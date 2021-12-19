#include "Interpreter.h"

void Interpreter::interpret(const Program& program) {
    scope_stack.init_global(std::map<std::string, FunctionDefinition*>());

    for( auto elem : program.instructions )
    {
        elem->be_handled( this );
    }
}

void Interpreter::interpret(ForEachLoop *for_each_loop) {

}

void Interpreter::interpret(FunctionCall *function_call) {
    auto func_def = scope_stack.get_function(function_call->getName());
    auto func_params = func_def->getParameters();

    auto func_args = function_call->getArguments().getArgs();
    // todo: porownac liczbe param i args
    // std::zip
    std::map<std::string, VariantValue*> call_init;

    for (int i = 0; i < func_params.size(); ++i)
    {
        func_args[i]->be_evaluated(this);
        call_init[func_params[i]] = scope_stack.get_last_result();
    }

    //todo: DONE stworzenie callcontext wewnatrz make_Call
    scope_stack.make_call(call_init);

    func_def->getBody()->be_handled(this);

    scope_stack.return_call();
}

void Interpreter::interpret(FunctionDefinition *function_definition) {
    scope_stack.make_func( function_definition->getName(), FunctionDefinition(*function_definition));
}

void Interpreter::interpret(If *if_statement) {
    if_statement->getCondition()->be_evaluated(this);
    if( scope_stack.get_last_result() )
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

    if( scope_stack.get_last_result() != nullptr )
    {
        for( int i = scope_stack.get_last_result()->to_number(); i > 0; i-- )
        {
            repeat_loop->getLoop()->be_handled(this);

            if( scope_stack.get_last_returned() != nullptr )
            {
                break;
            }
        }
    }
    else
        throw std::runtime_error("invalid repeat loop argument");
}

void Interpreter::interpret(WhileLoop *while_loop) {
    while_loop->getCondition()->be_evaluated(this);

    if( scope_stack.get_last_result()->to_bool() )
    {
        while_loop->getLoop()->be_handled(this);

        if( scope_stack.get_last_returned() != nullptr )
        {
            return;
        }

        while_loop->getCondition()->be_evaluated(this);
    }
    else
        throw std::runtime_error("invalid repeat loop argument");
}

void Interpreter::interpret(Return *return_statement) {
    return_statement->getValue()->be_evaluated(this);
    scope_stack.set_last_returned( scope_stack.get_last_result() );
}

void Interpreter::interpret(VariableAssignment *variable_assignment) {
    variable_assignment->getValue()->be_evaluated(this);

    scope_stack.set_var(variable_assignment->getLabel(), scope_stack.get_last_result());
}

void Interpreter::interpret(VariableDeclaration *variable_declaration) {
    if( scope_stack.is_symbol_defined(variable_declaration->getLabel()))
        throw std::runtime_error("symbol defined");
    variable_declaration->getValue()->be_evaluated(this);
    scope_stack.set_var(variable_declaration->getLabel(), scope_stack.get_last_result());
}

void Interpreter::interpret(Block *block) {
    // tworzenie scope bloku
    for(auto const & statement : block->getStatements())
    {
        statement->be_handled(this);
        if(scope_stack.get_last_returned() != nullptr )
        {
            break;
        }
    }
    // usuwanie scope bloku
}


void Interpreter::evaluate(OrCondition *or_condition) {
    auto expressions = or_condition->getElements();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result();

    //todo: chyba trzeba pominąc pierwszy, bo już był ewaluowany
    for( auto e : expressions )
    {
        e->be_evaluated(this);
        scope_stack.set_last_result( *left_val || scope_stack.get_last_result() );
    }
}

void Interpreter::evaluate(AndCondition *and_condition) {
    auto expressions = and_condition->getEqConditions();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result();

    //todo: to samo co wyżej
    for( auto e : expressions )
    {
        e->be_evaluated(this);
        scope_stack.set_last_result( *left_val && scope_stack.get_last_result() );
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
            scope_stack.set_last_result( new Bool( *left_val == scope_stack.get_last_result()));
        }
        else
        {
            scope_stack.set_last_result( new Bool( *left_val != scope_stack.get_last_result()));
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
                scope_stack.set_last_result( new Bool( *left_val < scope_stack.get_last_result() ) );
                break;
            case RelationType::LOWER_OR_EQUAL:
                scope_stack.set_last_result( new Bool( *left_val <= scope_stack.get_last_result() ));
                break;
            case RelationType::GREATER_OR_EQUAL:
                scope_stack.set_last_result( new Bool( *left_val >= scope_stack.get_last_result() ));
                break;
            case RelationType::GREATER:
                scope_stack.set_last_result( new Bool( *left_val > scope_stack.get_last_result() ));
                break;
            default:
                throw std::runtime_error("unknown comparision type");

        }
    }
}

void Interpreter::evaluate(AdditiveExpression *additive_expression) {
    additive_expression->getExpressions()[0]->be_evaluated(this);

    for( int i = 0; i < additive_expression->getOperators().size(); ++i )
    {
        auto left_val = scope_stack.get_last_result();

        auto op = additive_expression->getOperators()[i];
        auto exp = additive_expression->getExpressions()[i+1];

        exp->be_evaluated(this);

        switch( op.getType() )
        {
            case OperationType::SUM:
                scope_stack.set_last_result( *left_val + scope_stack.get_last_result());
                break;
            case OperationType::SUBSTRACTION:
                scope_stack.set_last_result( *left_val - scope_stack.get_last_result());
                break;
            default:
                throw std::runtime_error("unknown addition operator");
        }
    }
}

void Interpreter::evaluate(MultiplyExpression *multiply_expression) {
    multiply_expression->getElements()[0]->be_evaluated(this);


    for( int i = 0; i < multiply_expression->getOperators().size(); ++i )
    {
        auto left_val = scope_stack.get_last_result();

        auto op = multiply_expression->getOperators()[i];
        auto exp = multiply_expression->getElements()[i+1];

        exp->be_evaluated(this);

        switch( op.getType() )
        {
            case OperationType::MULTIPLY:
                scope_stack.set_last_result( *left_val * scope_stack.get_last_result());
                break;
            case OperationType::DIVIDE:
                scope_stack.set_last_result( *left_val / scope_stack.get_last_result());
                break;
            default:
                throw std::runtime_error("unknown multiply operator");
        }
    }
}

void Interpreter::evaluate(FunctionCall *function_call) {
    function_call->be_handled(this);
    scope_stack.set_last_result( scope_stack.get_last_returned() );
}

void Interpreter::evaluate(Bool *bool_val) {
    scope_stack.set_last_result(bool_val);
}

void Interpreter::evaluate(String *string_val) {
    scope_stack.set_last_result(string_val);
}

void Interpreter::evaluate(Number *num_val) {
    scope_stack.set_last_result(num_val);
}

void Interpreter::evaluate(ListOfVariantValues *list_val) {
    scope_stack.set_last_result(list_val);
}

void Interpreter::evaluate(Label *label_val) {
    scope_stack.set_last_result(scope_stack.get_var(label_val->get_variable_name()));
}

void Interpreter::evaluate(NegatedMathElement *negated_math_element) {
    negated_math_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result( new Number(-1 * scope_stack.get_last_result()->to_number()) );
}

void Interpreter::evaluate(NegatedLogicalElement *negated_logical_element) {
    negated_logical_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result(  new Bool(!scope_stack.get_last_result()->to_bool()) );
}

void Interpreter::evaluate(ListOfAssignable *list_val) {
    std::vector<VariantValue*> values;

    for( auto expression : list_val->get_elements() )
    {
        expression->be_evaluated( this );
        values.emplace_back( scope_stack.get_last_result() );
    }

    scope_stack.set_last_result( new ListOfVariantValues(values) );
}

void Interpreter::evaluate(RelationalCondition *multiply_expression) {

}
