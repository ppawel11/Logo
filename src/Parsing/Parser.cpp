#include "Parser.h"



Program Parser::parseProgram() {
    std::vector<std::unique_ptr<LanguageElement>> statements;
    std::map<std::string, std::unique_ptr<FunctionDefinition>> func_definitions;

    std::optional<std::unique_ptr<LanguageElement>> lang_element;
    std::optional<std::unique_ptr<FunctionDefinition>> func_definition;

    lexer.getNextToken();
    while(
            (lang_element = tryToParseLanguageElement()) ||
            (func_definition = tryToParseFuncDef())
         )
    {
        if( lang_element )
        {
            statements.push_back(std::move(lang_element.value()));
        }
        else
        {
            func_definitions[func_definition.value()->getName()] = std::move(func_definition.value());
        }
    }

    return Program( std::move(statements), std::move(func_definitions) );
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseLanguageElement() {
    std::optional<std::unique_ptr<LanguageElement>> statement;

    if((statement = tryToParseIf()) ||
       (statement = tryToParseLoop()) ||
       (statement = tryToParseSemicolonEnded()))
    {
        return statement;
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseSemicolonEnded(){
    std::optional<std::unique_ptr<LanguageElement>> statement;

    if((statement = tryToParseVarDeclaration()) ||
       (statement = tryToParseVarAssignmentOrFuncCall()) ||
       (statement = tryToParseReturn() ))
    {
        if( lexer.getCurrentToken().getType() != TokenType::SEMICOLON )
        {
            throw std::runtime_error("expected semicolon");
        }
        lexer.getNextToken();
        return statement;
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<FunctionDefinition>> Parser::tryToParseFuncDef() {
    if( lexer.getCurrentToken().getType() == TokenType::FUNC )
    {
        if( lexer.getNextToken().getType() != TokenType::LABEL )
        {
            throw std::runtime_error("func def invalid");
        }

        std::string func_name = lexer.getCurrentToken().getLiteralValue();

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("func def invalid");
        }

        std::vector<std::string> parameters;

        if( lexer.getNextToken().getType() == TokenType::LABEL )
        {
            parameters.push_back( lexer.getCurrentToken().getLiteralValue() );
            while( lexer.getNextToken().getType() == TokenType::COMMA )
            {
                if( lexer.getNextToken().getType() == TokenType::LABEL )
                {
                    parameters.push_back(lexer.getCurrentToken().getLiteralValue());
                }
                else
                {
                    throw std::runtime_error("func def invalid");
                }
            }
        }

        if( lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("func def invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> func_body = tryToParseBlock();

        if ( !(func_body) )
        {
            throw std::runtime_error("func def invalid");
        }

        return std::make_unique<FunctionDefinition>(func_name, parameters, std::move(func_body.value()));
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseBlock() {
    if (lexer.getCurrentToken().getType() == TokenType::CURLY_BRACKET_OPEN)
    {
        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> statement;
        std::vector<std::unique_ptr<LanguageElement>> statement_vec;

        while ((statement = tryToParseLanguageElement())) {
            statement_vec.push_back( std::move(  statement.value() ) );
        }

        if (lexer.getCurrentToken().getType() != TokenType::CURLY_BRACKET_CLOSE )
        {
            throw std::runtime_error("block invalid");
        }
        lexer.getNextToken();

        return std::make_unique<Block>( std::move(statement_vec) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseIf() {
    if( lexer.getCurrentToken().getType() == TokenType::IF )
    {
        std::optional<std::unique_ptr<Assignable>> condition;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("if invalid");
        }

        lexer.getNextToken();

        if(!(condition = tryToParseOrCondition()) ||
            lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("if invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> if_statement;
        std::optional<std::unique_ptr<LanguageElement>> else_statement = std::nullopt;

        if( !(if_statement = tryToParseBlock()) )
        {
            throw std::runtime_error("if invalid");
        }

        if( lexer.getCurrentToken().getType() == TokenType::ELSE )
        {
            if( !(else_statement = tryToParseBlock()) )
            {
                throw std::runtime_error("else invalid");
            }
            return std::make_unique<If>(std::move(condition.value()), std::move(if_statement.value()), std::move(else_statement.value()));
        }

        return std::make_unique<If>(std::move(condition.value()), std::move(if_statement.value()), std::nullopt );
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseLoop() {
    std::optional<std::unique_ptr<LanguageElement>> loop;

    if( (loop = tryToParseWhileLoop()) ||
        (loop = tryToParseForEachLoop()) ||
        (loop = tryToParseRepeatLoop()) )
    {
        return loop;
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseVarDeclaration() {
    if( lexer.getCurrentToken().getType() == TokenType::VAR )
    {
        if( lexer.getNextToken().getType() != TokenType::LABEL )
        {
            throw std::runtime_error("var declaration invalid");
        }

        std::string var_name = lexer.getCurrentToken().getLiteralValue();

        if( lexer.getNextToken().getType() != TokenType::ASSIGN )
        {
            throw std::runtime_error("var declaration invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<Assignable>> value = tryToParseAssignable();

        if( !value )
        {
            throw std::runtime_error("var declaration invalid");
        }

        return std::make_unique<VariableDeclaration>( var_name, std::move(value.value()) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseVarAssignmentOrFuncCall() {
    if( lexer.getCurrentToken().getType() == TokenType::LABEL )
    {
        std::optional<std::unique_ptr<LanguageElement>> label_started;
        std::string label = lexer.getCurrentToken().getLiteralValue();

        lexer.getNextToken();

        if((label_started = tryToParseVarAssignment(label)) ||
           (label_started = tryToParseFuncCall<LanguageElement>(label)) )
        {
            return label_started;
        }
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseVarAssignment(const std::string& label) {
    if( lexer.getCurrentToken().getType() == TokenType::ASSIGN )
    {
        std::optional<std::unique_ptr<Assignable>> assignable;

        lexer.getNextToken();

        if(!(assignable = tryToParseAssignable()))
        {
            throw std::runtime_error("var assignment invalid");
        }

        return std::make_unique<VariableAssignment>(label, std::move(assignable.value()) );
    }

    return std::nullopt;
}

template<typename T> std::optional<std::unique_ptr<T>> Parser::tryToParseFuncCall(const std::string& label) {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();

        std::optional<Arguments> arguments = tryToParseArguments();

        if( lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("func call arguments invalid");
        }

        lexer.getNextToken();

        if( arguments )
            return std::make_unique<FunctionCall>(label, std::move(arguments.value()));
        else
            return std::make_unique<FunctionCall>(label, Arguments());
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseWhileLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::WHILE )
    {
        std::optional<std::unique_ptr<Assignable>> condition;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("while invalid");
        }

        lexer.getNextToken();

        if(!(condition = tryToParseOrCondition()) ||
            lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("while invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> while_block;

        if( !(while_block = tryToParseBlock()) )
        {
            throw std::runtime_error("while_invalid");
        }

        return std::make_unique<WhileLoop>(std::move(condition.value()), std::move(while_block.value()));
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseForEachLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::FOR )
    {
        std::string element_label;
        std::string container_label;
        std::optional<std::unique_ptr<Assignable>> container;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN ||
            lexer.getNextToken().getType() != TokenType::LABEL)
        {
            throw std::runtime_error("for invalid");
        }

        element_label = lexer.getCurrentToken().getLiteralValue();

        if( lexer.getNextToken().getType() != TokenType::COLON )
        {
            throw std::runtime_error("for invalid");
        }

        lexer.getNextToken();

        container = tryToParseAssignable();
        if( container == std::nullopt )
        {
            throw std::runtime_error("for invalid");
        }

        if( lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("for invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> for_statements;

        if( !(for_statements = tryToParseBlock()) )
        {
            throw std::runtime_error("for invalid");
        }

        return std::make_unique<ForEachLoop>(element_label, std::move(container.value()), std::move(for_statements.value()));
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseRepeatLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::REPEAT )
    {
        std::optional<std::unique_ptr<Assignable>> number_of_repeats;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("repeat invalid");
        }

        lexer.getNextToken();

        if(!(number_of_repeats = tryToParseAdditiveExpression()) ||
            lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("repeat invalid");
        }

        lexer.getNextToken();

        std::optional<std::unique_ptr<LanguageElement>> repeat_statements;

        if( !(repeat_statements = tryToParseBlock()) )
        {
            throw std::runtime_error("repeat loop invalid");
        }

        return std::make_unique<RepeatLoop>(std::move(number_of_repeats.value()), std::move(repeat_statements.value()));
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<LanguageElement>> Parser::tryToParseReturn() {
    if( lexer.getCurrentToken().getType() == TokenType::RETURN )
    {
        std::optional<std::unique_ptr<LanguageElement>> return_statement;
        lexer.getNextToken();
        std::optional<std::unique_ptr<Assignable>> return_value = tryToParseAssignable();
        if( !return_value )
        {
            throw std::runtime_error("return invalid");
        }
        return std::make_unique<Return>(std::move(return_value.value()));
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseAssignable() {
    std::optional<std::unique_ptr<Assignable>> assignable;

    if(( assignable = tryToParseList() ) ||
       ( assignable = tryToParseOrCondition() ) ||
       ( assignable = tryToParseString() ) )
    {
        return assignable;
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseAdditiveExpression() {
    // additive = multiply, { addoperator, multiply }
    if( std::optional<std::unique_ptr<Assignable>> multiply_expression = tryToParseMultiplyExpression() )
    {
        std::vector<std::unique_ptr<Assignable>> expressions;
        std::vector<AdditiveOperator> operators;

        expressions.push_back( std::move(multiply_expression.value()) );

        while( lexer.getCurrentToken().getType() == TokenType::PLUS ||
               lexer.getCurrentToken().getType() == TokenType:: MINUS )
        {
            if( lexer.getCurrentToken().getType() == TokenType::PLUS )
            {
                operators.emplace_back(OperationType::SUM);
            }
            else
            {
                operators.emplace_back(OperationType::SUBSTRACTION);
            }

            lexer.getNextToken();

            if( !(multiply_expression = tryToParseMultiplyExpression()) )
            {
                throw std::runtime_error("parsing expression invalid");
            }

            expressions.push_back( std::move(multiply_expression.value()) );
        }

        return std::make_unique<AdditiveExpression>( std::move(expressions), operators );
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseMultiplyExpression() {
    // multiply = element, { muloperator, element }
    if( std::optional<std::unique_ptr<Assignable>> math_element = tryToParseMathElement() )
    {
        std::vector<std::unique_ptr<Assignable>> elements;
        std::vector<MultiplyOperator> operators;

        elements.push_back( std::move(math_element.value()) );

        while( lexer.getCurrentToken().getType() == TokenType::MULTIPLY ||
               lexer.getCurrentToken().getType() == TokenType::DIVIDE )
        {
            if( lexer.getCurrentToken().getType() == TokenType::MULTIPLY )
            {
                operators.emplace_back(OperationType::MULTIPLY );
            }
            else
            {
                operators.emplace_back(OperationType::DIVIDE );
            }

            lexer.getNextToken();

            if( !(math_element = tryToParseMathElement()) )
            {
                throw std::runtime_error("multiply expression invalid");
            }

            elements.push_back( std::move(math_element.value()) );
        }

        return std::make_unique<MultiplyExpression>( std::move(elements), operators );
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseMathElement() {
    bool is_negated = false;
    std::unique_ptr<Assignable> result = nullptr;

    if( lexer.getCurrentToken().getType() == TokenType::MINUS )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::NUMBER )
    {
        result = std::make_unique<Number>(lexer.getCurrentToken().getNumericValue());
        lexer.getNextToken();
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::LABEL )
    {
        std::string label = lexer.getCurrentToken().getLiteralValue();

        lexer.getNextToken();

        if( std::optional<std::unique_ptr<Assignable>> func_call = tryToParseFuncCall<Assignable>(label)) {
            result = std::move(func_call.value());
        }
        else
        {
            result = std::make_unique<Label>( label );
        }
    }
    else if( std::optional<std::unique_ptr<Assignable>> parent_expr = tryToParseParentExpression() )
    {
        result = std::move( parent_expr.value() );
    }

    if( result != nullptr )
    {
        if( is_negated )
        {
            return std::make_unique<NegatedMathElement>( std::move(result) );
        }
        return result;
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseList() {
    if ( lexer.getCurrentToken().getType() == TokenType::BRACKET_OPEN )
    {
        std::vector<std::unique_ptr<Assignable>> elements;
        lexer.getNextToken();
        if( std::optional<std::unique_ptr<Assignable>> elem = tryToParseAssignable() )
        {
            elements.push_back( std::move(elem.value()));
            while( lexer.getCurrentToken().getType() == TokenType::COMMA )
            {
                lexer.getNextToken();
                if( (elem = tryToParseAssignable()) )
                {
                    elements.push_back(std::move(elem.value()));
                }
                else
                {
                    throw std::runtime_error("elements invalid");
                }
            }

            if( lexer.getCurrentToken().getType() != TokenType::BRACKET_CLOSE )
                throw std::runtime_error("list invalid");
            lexer.getNextToken();
            return std::make_unique<ListOfAssignable>( std::move(elements) );
        }
    }
    return std::nullopt;
}

std::optional<Arguments> Parser::tryToParseArguments() {
    if( std::optional<std::unique_ptr<Assignable>> arg = tryToParseAssignable() )
    {
        std::vector<std::unique_ptr<Assignable>> args;
        args.push_back(std::move(arg.value()));
        while( lexer.getCurrentToken().getType() == TokenType::COMMA )
        {
            lexer.getNextToken();
            if( (arg = tryToParseAssignable()) )
            {
                args.push_back(std::move(arg.value()));
            }
            else
            {
                throw std::runtime_error("args invalid");
            }
        }
        return Arguments( std::move(args) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseParentExpression() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
//        if ( std::optional<std::unique_ptr<Assignable>> expr = tryToParseAdditiveExpression() )
        if ( std::optional<std::unique_ptr<Assignable>> expr = tryToParseOrCondition() )
        {
            if ( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_CLOSE )
            {
                lexer.getNextToken();
                return expr;
            }
        }

        throw std::runtime_error("invalid parent expression");
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseString() {
    if( lexer.getCurrentToken().getType() == TokenType::STRING )
    {
        auto str = std::make_unique<String>( lexer.getCurrentToken().getLiteralValue() );
        lexer.getNextToken();
        return str;
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseOrCondition() {
    // condition = andCond, { orOp, andCond }
    if( std::optional<std::unique_ptr<Assignable>> condition = tryToParseAndCondition() )
    {
        std::vector<std::unique_ptr<Assignable>> conditions;

        conditions.push_back( std::move(condition.value()) );

        while( lexer.getCurrentToken().getType() == TokenType::OR_SYMBOLIC ||
               lexer.getCurrentToken().getType() == TokenType::OR )
        {
            lexer.getNextToken();
            if( (condition = tryToParseAndCondition()) )
            {
                conditions.push_back( std::move(condition.value()) );
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return std::make_unique<OrCondition>( std::move(conditions) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseAndCondition() {
    // and_condition = eqCond, { andOp, eqCond }
    if( std::optional<std::unique_ptr<Assignable>> condition = tryToParseEqualityCondition() )
    {
        std::vector<std::unique_ptr<Assignable>> conditions;

        conditions.push_back( std::move(condition.value()) );

        while( lexer.getCurrentToken().getType() == TokenType::AND_SYMBOLIC ||
               lexer.getCurrentToken().getType() == TokenType::AND )
        {
            lexer.getNextToken();
            if( (condition = tryToParseEqualityCondition()) )
            {
                conditions.push_back( std::move(condition.value()) );
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }
        return std::make_unique<AndCondition>( std::move(conditions) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseEqualityCondition() {
    // eq_cond = relational_cond, [ eqOP, relational_cond ]
    if( std::optional<std::unique_ptr<Assignable>> first_condition = tryToParseRelationalCondition() )
    {

        if( lexer.getCurrentToken().getType() == TokenType::EQUAL ||
            lexer.getCurrentToken().getType() == TokenType::NOT_EQUAL )
        {
            bool equals = lexer.getCurrentToken().getType() == TokenType::EQUAL;

            lexer.getNextToken();

            if( std::optional<std::unique_ptr<Assignable>> second_condition = tryToParseRelationalCondition() )
            {
                return std::make_unique<EqualityCondition>(
                        std::move(first_condition.value()),
                        equals,
                        std::move(second_condition.value())
                );
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return std::make_unique<EqualityCondition>( std::move(first_condition.value()) );
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseRelationalCondition() {
    bool is_negated = false;
    std::optional<std::unique_ptr<Assignable>> result = std::nullopt;

    if( lexer.getCurrentToken().getType() == TokenType::NEGATION )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::FALSE )
    {
        lexer.getNextToken();
        result = std::make_unique<Bool>(false);
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::TRUE )
    {
        lexer.getNextToken();
        result = std::make_unique<Bool>( true);
    }
    else if ( std::optional<std::unique_ptr<Assignable>> comparison = tryToParseComparison() )
    {
        result = std::move(comparison.value());
    }
    else if( std::optional<std::unique_ptr<Assignable>> parent_condition = tryToParseParentCondition() )
    {
        result = std::move(parent_condition.value());
    }

    if( is_negated && result != std::nullopt )
    {
        return std::make_unique<NegatedLogicalElement>( std::move(result.value()) );
    }
    return result;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseParentCondition() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
        if ( std::optional<std::unique_ptr<Assignable>> cond = tryToParseOrCondition() )
        {
            if ( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_CLOSE )
            {
                lexer.getNextToken();
                return cond;
            }
        }
        throw std::runtime_error("invalid parent condition");
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Assignable>> Parser::tryToParseComparison() {
    if( std::optional<std::unique_ptr<Assignable>> first_element = tryToParseAdditiveExpression() )
    {
        if( lexer.getCurrentToken().getType() == TokenType::LOWER_OR_EQUAL ||
            lexer.getCurrentToken().getType() == TokenType::LOWER ||
            lexer.getCurrentToken().getType() == TokenType::GREATER ||
            lexer.getCurrentToken().getType() == TokenType::GREATER_OR_EQUAL )
        {
            RelationType relation;

            if( lexer.getCurrentToken().getType() == TokenType::LOWER )
                relation = RelationType::LOWER;
            else if( lexer.getCurrentToken().getType() == TokenType::LOWER_OR_EQUAL )
                relation = RelationType::LOWER_OR_EQUAL;
            else if( lexer.getCurrentToken().getType() == TokenType::GREATER_OR_EQUAL )
                relation = RelationType::GREATER_OR_EQUAL;
            else
                relation = RelationType::GREATER;

            lexer.getNextToken();

            if( std::optional<std::unique_ptr<Assignable>> second_element = tryToParseAdditiveExpression() )
            {
                return std::make_unique<Comparison>( std::move(first_element.value()), relation, std::move(second_element.value()));
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return std::make_unique<Comparison>( std::move(first_element.value()) );
    }
    return std::nullopt;
}

