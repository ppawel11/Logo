#include "Interpreter.h"

void Interpreter::interpret(const Program& program) {
    scope_stack.init_global(std::map<std::string, std::unique_ptr<FunctionDefinition>>());

    for( auto const & elem : program.instructions )
    {
        elem->be_handled( this );
    }
}

void Interpreter::interpret(ForEachLoop *for_each_loop) {

}

void Interpreter::interpret(FunctionCall *function_call) {
    const auto & func_def = scope_stack.get_function(function_call->getName());
    auto func_params = func_def->getParameters();

    const auto & func_args = function_call->getArguments().getArgs();

    if (func_params.size() != func_args.size() )
        throw std::runtime_error("invalid number of arguments");

    std::map<std::string, std::unique_ptr<VariantValue>> call_init;

    for (int i = 0; i < func_params.size(); ++i)
    {
        func_args[i]->be_evaluated(this);
        call_init[func_params[i]] = std::move(scope_stack.get_last_result());
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

            if( scope_stack.get_last_result() != nullptr )
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

    while( scope_stack.get_last_result()->to_bool() )
    {
        while_loop->getLoop()->be_handled(this);

        if( scope_stack.get_last_result() != nullptr )
        {
            return;
        }

        while_loop->getCondition()->be_evaluated(this);
    }
}

void Interpreter::interpret(Return *return_statement) {
    return_statement->getValue()->be_evaluated(this);
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
        if(scope_stack.get_last_result() != nullptr )
        {
            break;
        }
    }
    // usuwanie scope bloku
}


void Interpreter::evaluate(OrCondition *or_condition) {
    //todo: nie ewaluować jeśli znalazł true
    const auto & expressions = or_condition->getElements();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result().get();

    for( int i = 1; i < expressions.size(); ++i )
    {
        expressions[i]->be_evaluated(this);
        scope_stack.set_last_result( ( *left_val || scope_stack.get_last_result().get() ) );
    }
}

void Interpreter::evaluate(AndCondition *and_condition) {
    // todo: nie ewaluować jeśli znalazł false
    const auto & expressions = and_condition->getEqConditions();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result().get();

    for( int i = 1; i < expressions.size(); ++i )
    {
        expressions[i]->be_evaluated(this);
        // todo: wykomentowane
//        scope_stack.set_last_result(  *left_val && scope_stack.get_last_result().get() );
    }
}

void Interpreter::evaluate(EqualityCondition *equality_condition) {
    equality_condition->getFirstCondition()->be_evaluated(this);

    if( equality_condition->getEquals() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result().get();

        equality_condition->getSecondCondition().value()->be_evaluated(this);

        if( equality_condition->getEquals().value() )
        {
            scope_stack.set_last_result(*left_val == scope_stack.get_last_result().get() );
        }
        else
        {
            scope_stack.set_last_result( *left_val != scope_stack.get_last_result().get() );
        }
    }
}

//todo: dla wszystkich typów wszystkie operacje
std::unique_ptr<VariantValue> dodaj(const Bool& a, const Bool &  b)
{

}

void Interpreter::evaluate(Comparison *comparison) {
    comparison->getFirstExpression()->be_evaluated(this);

    if( comparison->getType() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result().get();

        comparison->getSecondExpression().value()->be_evaluated(this);

        switch( comparison->getType().value() )
        {
            case RelationType::LOWER:
                scope_stack.set_last_result(  *left_val < scope_stack.get_last_result().get() );
                break;
            case RelationType::LOWER_OR_EQUAL:
                scope_stack.set_last_result( *left_val <= scope_stack.get_last_result().get() );
                break;
            case RelationType::GREATER_OR_EQUAL:
                scope_stack.set_last_result(  *left_val >= scope_stack.get_last_result().get() );
                break;
            case RelationType::GREATER:
                scope_stack.set_last_result( *left_val > scope_stack.get_last_result().get() );
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
        auto left_val = scope_stack.get_last_result().get();

        auto op = additive_expression->getOperators()[i];
        additive_expression->getExpressions()[i+1]->be_evaluated(this);

        switch( op.getType() )
        {
            case OperationType::SUM:
                scope_stack.set_last_result( *left_val + scope_stack.get_last_result().get());
                break;
            case OperationType::SUBSTRACTION:
                scope_stack.set_last_result( *left_val - scope_stack.get_last_result().get());
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
        auto left_val = scope_stack.get_last_result().get();

        auto op = multiply_expression->getOperators()[i];
        multiply_expression->getElements()[i+1]->be_evaluated( this );

        switch( op.getType() )
        {
            case OperationType::MULTIPLY:
                scope_stack.set_last_result( *left_val * scope_stack.get_last_result().get());
                break;
            case OperationType::DIVIDE:
                scope_stack.set_last_result( *left_val / scope_stack.get_last_result().get());
                break;
            default:
                throw std::runtime_error("unknown multiply operator");
        }
    }
}

void Interpreter::evaluate(FunctionCall *function_call) {
    function_call->be_handled(this);
}

void Interpreter::evaluate(Bool *bool_val) {
    scope_stack.set_last_result( std::make_unique<Bool>( bool_val->to_bool() ) );
}

void Interpreter::evaluate(String *string_val) {
    scope_stack.set_last_result( std::make_unique<String>(string_val->to_string()));
}

void Interpreter::evaluate(Number *num_val) {
    scope_stack.set_last_result( std::make_unique<Number>(num_val->to_number()));
}

void Interpreter::evaluate(ListOfVariantValues *list_val) {
    scope_stack.set_last_result( std::make_unique<ListOfVariantValues>(list_val->to_list()));
}

void Interpreter::evaluate(Label *label_val) {
    scope_stack.set_last_result(scope_stack.get_var(label_val->get_variable_name()));
}

void Interpreter::evaluate(NegatedMathElement *negated_math_element) {
    negated_math_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result( Number(-1) * scope_stack.get_last_result().get());
}

void Interpreter::evaluate(NegatedLogicalElement *negated_logical_element) {
    negated_logical_element->getElement()->be_evaluated(this);
    scope_stack.set_last_result( std::make_unique<Bool>(!scope_stack.get_last_result()->to_bool()) );
}

void Interpreter::evaluate(ListOfAssignable *list_val) {
    std::vector<std::shared_ptr<VariantValue>> values;

    for( const auto & expression : list_val->get_elements() )
    {
        expression->be_evaluated( this );
        values.emplace_back(scope_stack.get_last_result().get() );
    }

    scope_stack.set_last_result( std::make_unique<ListOfVariantValues>(values) );
}
