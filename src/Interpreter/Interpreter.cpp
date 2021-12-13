#include "Interpreter.h"

void Interpreter::interpret(const Program& program) {
    scope_stack.init_global(std::map<std::string, FunctionDefinition>());

    for( auto elem : program.instructions )
    {
        elem->be_handled( this );
    }
}

void Interpreter::interpret(ForEachLoop *for_each_loop) {

}

void Interpreter::interpret(FunctionCall *function_call) {
    auto func_params = scope_stack.get_function(function_call->getName())->getParameters();
    auto func_args = function_call->getArguments().getArgs();

    std::map<std::string, Assignable*> call_init;

    for (int i = 0; i < func_params.size(); ++i)
    {
        func_args[i]->be_evaluated(this);
        call_init[func_params[i]] = scope_stack.get_last_result().value();
    }

    scope_stack.make_call(call_init);

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

    if( std::holds_alternative<int>(scope_stack.get_last_result().value()) )
    {
        for( int i = std::get<int>(scope_stack.get_last_result().value()); i > 0; i-- )
        {
            repeat_loop->getLoop()->be_handled(this);

            if( scope_stack.get_last_returned() != std::nullopt )
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

    if( std::holds_alternative<bool>(scope_stack.get_last_result().value()) )
    {
        while_loop->getLoop()->be_handled(this);

        if( scope_stack.get_last_returned() != std::nullopt )
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
    scope_stack.set_last_returned( scope_stack.get_last_result().value() );
}

void Interpreter::interpret(VariableAssignment *variable_assignment) {
    variable_assignment->getValue()->be_evaluated(this);

    scope_stack.set_var(variable_assignment->getLabel(), scope_stack.get_last_result().value());
}

void Interpreter::interpret(VariableDeclaration *variable_declaration) {
    if( scope_stack.is_symbol_defined(variable_declaration->getLabel()))
        throw std::runtime_error("symbol defined");
    //todo: powinna być ewaluacja
    scope_stack.set_var(variable_declaration->getLabel(), variable_declaration->getValue());
}

void Interpreter::interpret(Block *block) {
    // tworzenie scope bloku
    for(auto const & statement : block->getStatements())
    {
        statement->be_handled(this);
        if(scope_stack.get_last_returned() != std::nullopt )
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

    for( auto e : expressions )
    {
        e->be_evaluated(this);

        left_val = left_val || std::get<bool>(scope_stack.get_last_result().value());
    }

    scope_stack.set_last_result( left_val.value() );
}

void Interpreter::evaluate(AndCondition *and_condition) {
    auto expressions = and_condition->getEqConditions();

    expressions[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result();

    for( auto e : expressions )
    {
        e->be_evaluated(this);

        left_val = left_val && std::get<bool>(scope_stack.get_last_result().value());
    }

    scope_stack.set_last_result( left_val.value() );
}

void Interpreter::evaluate(EqualityCondition *equality_condition) {
    equality_condition->getFirstCondition()->be_evaluated(this);

    if( equality_condition->getEquals() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result().value();

        equality_condition->getSecondCondition().value()->be_evaluated(this);

        if( equality_condition->getEquals().value() )
        {
            left_val = (left_val == scope_stack.get_last_result().value());
        }else
        {
            left_val = (left_val != scope_stack.get_last_result().value() );
        }

        scope_stack.set_last_result(left_val);
    }
}

void Interpreter::evaluate(Comparison *comparison) {
    comparison->getFirstExpression()->be_evaluated(this);

    if( comparison->getType() != std::nullopt )
    {
        auto left_val = scope_stack.get_last_result().value();

        comparison->getSecondExpression().value()->be_evaluated(this);

        if( comparison->getType().value() == RelationType::LOWER )
        {
            left_val = (left_val < scope_stack.get_last_result().value());
        }else if( comparison->getType().value() == RelationType::LOWER_OR_EQUAL)
        {
            left_val = (left_val <= scope_stack.get_last_result().value() );
        }else if( comparison->getType().value() == RelationType::GREATER_OR_EQUAL)
        {
            left_val = (left_val >= scope_stack.get_last_result().value() );
        }else
        {
            left_val = (left_val > scope_stack.get_last_result().value() );
        }

        scope_stack.set_last_result(left_val);
    }
}

void Interpreter::evaluate(AdditiveExpression *additive_expression) {
    additive_expression->getExpressions()[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result().value();

    for( int i = 0; i < additive_expression->getOperators().size(); ++i )
    {
        auto op = additive_expression->getOperators()[i];
        auto exp = additive_expression->getExpressions()[i+1];

        exp->be_evaluated(this);

        if( op.getType() == OperationType::SUM )
        {
            left_val += scope_stack.get_last_result().value();
        }else
        {
            left_val -= scope_stack.get_last_result().value();
        }
    }

    scope_stack.set_last_result( left_val );
}

void Interpreter::evaluate(MultiplyExpression *multiply_expression) {
    multiply_expression->getElements()[0]->be_evaluated(this);

    auto left_val = scope_stack.get_last_result().value();

    for( int i = 0; i < multiply_expression->getOperators().size(); ++i )
    {
        auto op = multiply_expression->getOperators()[i];
        auto exp = multiply_expression->getElements()[i+1];

        exp->be_evaluated(this);

        if( op.getType() == OperationType::MULTIPLY )
        {
            left_val *= scope_stack.get_last_result().value();
        }else
        {
            left_val /= scope_stack.get_last_result().value();
        }
    }

    scope_stack.set_last_result( left_val );
}

void Interpreter::evaluate(FunctionCall *function_call) {
    function_call->be_handled(this);
    scope_stack.set_last_result( scope_stack.get_last_returned().value() );
}

void Interpreter::evaluate(Bool *bool_val) {
    scope_stack.set_last_result(bool_val->get_value());
}

void Interpreter::evaluate(String *string_val) {
    scope_stack.set_last_result(string_val->get_value());
}

void Interpreter::evaluate(Number *num_val) {
    scope_stack.set_last_result(num_val->get_value());
}

void Interpreter::evaluate(List *list_val) {
    scope_stack.set_last_result(list_val->get_elements());
}

void Interpreter::evaluate(Label *label_val) {
    auto var = scope_stack.get_var(label_val->getLabel());

    var->be_evaluated(this);
}

void Interpreter::evaluate(NegatedMathElement *negated_math_element) {
    negated_math_element->be_evaluated(this);
    scope_stack.set_last_result( -1 * scope_stack.get_last_result().value() );
}

void Interpreter::evaluate(NegatedLogicalElement *negated_logical_element) {
    negated_logical_element->be_evaluated(this);
    scope_stack.set_last_result(  !scope_stack.get_last_result().value() );
}
