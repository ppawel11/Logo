#include "Interpreter.h"

//func trojkat( bok ) {
//    repeat(3) {
//        forward(bok);
//        turn(120);
//    }
//}
//
//func dywan( bok, ile ) {
//    if( ile == 0 ) {
//        trojkat(bok);
//    }
//    else {
//        repeat(3) {
//            dywan(bok/2, ile-1);
//            forward(bok);
//            turn(120);
//        }
//    }
//}

void Interpreter::interpret(Program *program ) {
    try {
        if( program == nullptr )
        {
            throw InterpreterException("Program undefined");
        }

        for( auto& func_def : program->func_defs )
        {
            if( std::find( tkom::std_lib::function_names.begin(), tkom::std_lib::function_names.end(), func_def.first ) != tkom::std_lib::function_names.end() )
            {
                throw InterpreterException("Redefinition of standard " + func_def.first + " function");
            }
        }

        scope_stack.init_global( std::move( program->func_defs ) );

        for( auto const & elem : program->instructions )
        {
            elem->be_handled( this );
        }

        scope_stack.return_call();
    } catch( InterpreterException & e) {
        emit error( QString::fromStdString("Interpreter: " + std::string(e.what())));
    } catch( std::runtime_error & e ) {
        emit error( QString::fromStdString("Interpreter: " + std::string(e.what())));
    }
}

void Interpreter::interpret(ForEachLoop *for_each_loop) {
    for_each_loop->getContainer()->be_evaluated( this );
    auto list = std::visit( Caster<std::vector<std::variant<Number, Bool, String, ListOfVariantValues>>> {}, scope_stack.get_last_result().value() );
    for( const auto& var : list )
    {
        scope_stack.set_var( for_each_loop->getValueLabel(), var );
        for_each_loop->getLoop()->be_handled( this );
    }
}



void Interpreter::interpret(FunctionCall *function_call) {
    const auto & func_def = scope_stack.get_function(function_call->getName());

    auto func_params = func_def->getParameters();
    const auto & func_args = function_call->getArguments().getArgs();

    if (func_params.size() != func_args.size() )
        throw InterpreterException("invalid number of arguments");

    std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> call_init;

    for (int i = 0; i < func_params.size(); ++i)
    {
        func_args[i]->be_evaluated(this);
        call_init[func_params[i]] = scope_stack.get_last_result().value();
    }

    scope_stack.make_call(call_init);

    func_def->getBody()->be_handled(this);

    scope_stack.return_call();

}

void Interpreter::interpret(FunctionDefinition *function_definition) {
    scope_stack.make_func( function_definition->getName(), std::make_unique<FunctionDefinition>( std::move(*function_definition )) );
}

void Interpreter::interpret(If *if_statement) {
    if_statement->getCondition()->be_evaluated(this);
    if( std::visit( Caster<bool> {}, scope_stack.get_last_result().value() ) )
    {
        if_statement->getIfBlock()->be_handled(this);
    }
    else
    {
        if( if_statement->getElseBlock() != std::nullopt )
        {
            if_statement->getElseBlock().value()->be_handled(this);
        }
    }
}

void Interpreter::interpret(RepeatLoop *repeat_loop) {
    repeat_loop->getRepeats()->be_evaluated(this);

    if( scope_stack.get_last_result() )
    {
        auto limit = std::visit(Caster<int> {}, scope_stack.get_last_result().value());
        for( int i = 0; i < limit; ++i )
        {
            repeat_loop->getLoop()->be_handled(this);

            if( scope_stack.isReturned() )
            {
                return;
            }
        }
    }
    else
        throw InterpreterException("invalid repeat loop argument");
}

void Interpreter::interpret(WhileLoop *while_loop) {
    while_loop->getCondition()->be_evaluated(this);

    while( std::visit(Caster<bool> {}, scope_stack.get_last_result().value()) )
    {
        while_loop->getLoop()->be_handled(this);

        if( scope_stack.isReturned() )
        {
            return;
        }

        while_loop->getCondition()->be_evaluated(this);
    }
}

void Interpreter::interpret(Return *return_statement) {
    return_statement->getValue()->be_evaluated(this);
    scope_stack.setReturned( true );
}

void Interpreter::interpret(VariableAssignment *variable_assignment) {
    variable_assignment->getValue()->be_evaluated(this);
    scope_stack.set_var(variable_assignment->getLabel(), scope_stack.get_last_result().value());
}

void Interpreter::interpret(VariableDeclaration *variable_declaration) {
    if( scope_stack.is_symbol_defined(variable_declaration->getLabel()))
        throw InterpreterException("symbol defined");
    variable_declaration->getValue()->be_evaluated(this);
    scope_stack.set_var(variable_declaration->getLabel(), scope_stack.get_last_result().value());
}

void Interpreter::interpret(Block *block) {
    scope_stack.make_scope();

    for(auto const & statement : block->getStatements())
    {
        statement->be_handled(this);

        if( scope_stack.isReturned() )
        {
            scope_stack.end_scope();
            return;
        }
    }

    scope_stack.end_scope();
}

void Interpreter::evaluate(OrCondition *or_condition) {
    const auto & expressions = or_condition->getElements();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result();


    for( int i = 1; i < expressions.size(); ++i )
    {
        if( std::visit(Caster<bool> {}, scope_stack.get_last_result().value() ) )
        {
            return;
        }

        expressions[i]->be_evaluated(this);
        scope_stack.set_last_result( std::visit( OrExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
    }
}

void Interpreter::evaluate(AndCondition *and_condition) {
    const auto & expressions = and_condition->getEqConditions();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result();

    for( int i = 1; i < expressions.size(); ++i )
    {
        if( !std::visit(Caster<bool> {}, scope_stack.get_last_result().value() ) )
        {
            return;
        }

        expressions[i]->be_evaluated(this);
        scope_stack.set_last_result(  std::visit( AndExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
    }
}

void Interpreter::evaluate(EqualityCondition *equality_condition) {
    equality_condition->getFirstCondition()->be_evaluated(this);

    if( equality_condition->getEquals() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result();

        equality_condition->getSecondCondition().value()->be_evaluated(this);

        if( equality_condition->getEquals().value() )
        {
            scope_stack.set_last_result(std::visit( EqualityExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
        }
        else
        {
            scope_stack.set_last_result( Bool( !(std::visit(Caster<bool> {}, std::visit( EqualityExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) ) ) ) );
        }
    }
}

void Interpreter::evaluate(Comparison *comparison) {
    comparison->getFirstExpression()->be_evaluated(this);

    if( comparison->getType() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result();

        comparison->getSecondExpression().value()->be_evaluated(this);

        switch( comparison->getType().value() )
        {
            case RelationType::LOWER:
                scope_stack.set_last_result(  std::visit( LessExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            case RelationType::LOWER_OR_EQUAL:
                scope_stack.set_last_result( std::visit( LessOrEqualExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            case RelationType::GREATER_OR_EQUAL:
                scope_stack.set_last_result(  std::visit( GreaterOrEqualExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            case RelationType::GREATER:
                scope_stack.set_last_result( std::visit( GreaterExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            default:
                throw InterpreterException("unknown comparision type");

        }
    }
}

void Interpreter::evaluate(AdditiveExpression *additive_expression) {
    additive_expression->getExpressions()[0]->be_evaluated(this);

    for( int i = 0; i < additive_expression->getOperators().size(); ++i )
    {
        auto left_val = scope_stack.get_last_result();

        auto op = additive_expression->getOperators()[i];
        additive_expression->getExpressions()[i+1]->be_evaluated(this);

        switch( op.getType() )
        {
            case OperationType::SUM:
                scope_stack.set_last_result( std::visit( SumExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            case OperationType::SUBSTRACTION:
                scope_stack.set_last_result( std::visit( SubtractionExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            default:
                throw InterpreterException("unknown addition operator");
        }
    }
}

void Interpreter::evaluate(MultiplyExpression *multiply_expression) {
    multiply_expression->getElements()[0]->be_evaluated(this);


    for( int i = 0; i < multiply_expression->getOperators().size(); ++i )
    {
        auto left_val = scope_stack.get_last_result();

        auto op = multiply_expression->getOperators()[i];
        multiply_expression->getElements()[i+1]->be_evaluated( this );

        switch( op.getType() )
        {
            case OperationType::MULTIPLY:
                scope_stack.set_last_result( std::visit( MultiplicationExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            case OperationType::DIVIDE:
                scope_stack.set_last_result( std::visit( DivisionExecutor {}, left_val.value(), scope_stack.get_last_result().value() ) );
                break;
            default:
                throw InterpreterException("unknown multiply operator");
        }
    }
}

void Interpreter::evaluate(FunctionCall *function_call) {
    function_call->be_handled(this);
}

void Interpreter::evaluate(Bool *bool_val) {
    scope_stack.set_last_result( *bool_val );
}

void Interpreter::evaluate(String *string_val) {
    scope_stack.set_last_result( *string_val );
}

void Interpreter::evaluate(Number *num_val) {
    scope_stack.set_last_result( *num_val );
}

void Interpreter::evaluate(ListOfVariantValues *list_val) {
    scope_stack.set_last_result( *list_val );
}

void Interpreter::evaluate(Label *label_val) {
    scope_stack.set_last_result(scope_stack.get_var(label_val->get_variable_name()));
}

void Interpreter::evaluate(NegatedMathElement *negated_math_element) {
    negated_math_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result( Number(!std::visit(  Caster<int> {}, scope_stack.get_last_result().value() ) ) );
}

void Interpreter::evaluate(NegatedLogicalElement *negated_logical_element) {
    negated_logical_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result( Bool( !std::visit(  Caster<bool> {}, scope_stack.get_last_result().value() ) ) );
}

void Interpreter::evaluate(ListOfAssignable *list_val) {
    std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> values;

    for( const auto & expression : list_val->get_elements() )
    {
        expression->be_evaluated( this );
        values.emplace_back( scope_stack.get_last_result().value() );
    }

    scope_stack.set_last_result( ListOfVariantValues(values) );
}

//void Interpreter::write() {
//    io_controller.write( std::visit( Caster<std::string> {}, scope_stack.get_last_result().value() ) );
//}
//
//void Interpreter::read() {
//    scope_stack.set_last_result( String(io_controller.read() ) );
//}
//
//void Interpreter::forward() {
//    drawing_controller->draw_line( std::visit( Caster<int> {}, scope_stack.get_last_result().value() ) );
//}
//
//void Interpreter::backward() {
//    drawing_controller->draw_line( -1 * std::visit( Caster<int> {}, scope_stack.get_last_result().value() ) );
//}
//
//void Interpreter::circle() {
//    drawing_controller->draw_circle( std::visit( Caster<int> {}, scope_stack.get_last_result().value() ) );
//}
//
//void Interpreter::turn() {
//    drawing_controller->turn( std::visit( Caster<int> {}, scope_stack.get_last_result().value() ) );
//}
//
//void Interpreter::reset() {
//    drawing_controller->reset();
//}
//
//void Interpreter::clear() {
//    drawing_controller->clear();
//}
//
//void Interpreter::switch_() {
//    drawing_controller->switch_mode();
//}

DrawingController *Interpreter::get_drawing_controller() const {
    return drawing_controller;
}

void Interpreter::set_drawing_controller(DrawingController *drawingController) {
    drawing_controller = drawingController;
    emit drawing_controller_changed();
}

void Interpreter::interpret(Backward *backward) {
    drawing_controller->draw_line( -1 * std::visit( Caster<int> {}, scope_stack.get_var("length") ) );
}

void Interpreter::interpret(Circle *circle) {
    drawing_controller->draw_circle( std::visit( Caster<int> {}, scope_stack.get_var("radius") ) );
}

void Interpreter::interpret(Clear *clear) {
    drawing_controller->clear();
}

void Interpreter::interpret(Read *read) {
    scope_stack.set_last_result( String(io_controller.read() ) );
}

void Interpreter::interpret(Forward *forward) {
    drawing_controller->draw_line( std::visit( Caster<int> {}, scope_stack.get_var("length") ) );
}

void Interpreter::interpret(Reset *reset) {
    drawing_controller->reset();
}

void Interpreter::interpret(Switch *switch_) {
    drawing_controller->switch_mode();
}

void Interpreter::interpret(Turn *turn) {
    drawing_controller->turn( std::visit( Caster<int> {}, scope_stack.get_var("angle") ) );
}

void Interpreter::interpret(Write *write) {
    io_controller.write( std::visit( Caster<std::string> {}, scope_stack.get_last_result().value() ) );
}
