#include "Parser.h"


Program Parser::parseProgram() {
    std::vector<LanguageElement*> statements;
    std::map<std::string, FunctionDefinition> func_definitions;

    std::optional<LanguageElement*> lang_element;
    std::optional<FunctionDefinition> func_definition;

    lexer.getNextToken();
    while(
            (lang_element = tryToParseLanguageElement()) ||
            (func_definition = tryToParseFuncDef())
         )
    {
        if( lang_element )
        {
            statements.push_back(lang_element.value());
        }
    }

    return Program(statements, std::map<std::string, FunctionDefinition>());
}

std::optional<LanguageElement *> Parser::tryToParseLanguageElement() {
    std::optional<LanguageElement*> statement;

    if((statement = tryToParseIf()) ||
       (statement = tryToParseLoop()) ||
       (statement = tryToParseSemicolonEnded()))
    {
        return statement;
    }

    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseSemicolonEnded(){
    std::optional<LanguageElement*> statement;

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

std::optional<FunctionDefinition> Parser::tryToParseFuncDef() {
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

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("func def invalid");
        }

        lexer.getNextToken();

        std::optional<LanguageElement*> func_body = tryToParseBlock();

        if ( !(func_body) )
        {
            throw std::runtime_error("func def invalid");
        }

        return FunctionDefinition(func_name, parameters, func_body.value());
    }

    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseBlock() {
    if (lexer.getCurrentToken().getType() == TokenType::CURLY_BRACKET_OPEN)
    {
        lexer.getNextToken();

        std::optional<LanguageElement*> statement;
        std::vector<std::unique_ptr<LanguageElement>> statement_vec;

        while ((statement = tryToParseLanguageElement())) {
            statement_vec.push_back( std::make_unique<LanguageElement>(*statement.value()) );
        }

        if (lexer.getCurrentToken().getType() != TokenType::CURLY_BRACKET_CLOSE )
        {
            throw std::runtime_error("block invalid");
        }
        lexer.getNextToken();

        return new Block(statement_vec);
    }
    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseIf() {
    if( lexer.getCurrentToken().getType() == TokenType::IF )
    {
        std::optional<Assignable*> condition;

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

        std::optional<LanguageElement*> if_statement;
        std::optional<LanguageElement*> else_statement = std::nullopt;

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
        }

        return new If(condition.value(), if_statement.value(), else_statement);
    }

    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseLoop() {
    std::optional<LanguageElement*> loop;

    if( (loop = tryToParseWhileLoop()) ||
        (loop = tryToParseForEachLoop()) ||
        (loop = tryToParseRepeatLoop()) )
    {
        return loop;
    }

    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseVarDeclaration() {
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

        std::optional<Assignable*> value = tryToParseAssignable();

        if( !value )
        {
            throw std::runtime_error("var declaration invalid");
        }

        return new VariableDeclaration( var_name, value.value() );
    }
    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseVarAssignmentOrFuncCall() {
    if( lexer.getCurrentToken().getType() == TokenType::LABEL )
    {
        std::optional<LanguageElement*> label_started;
        std::string label = lexer.getCurrentToken().getLiteralValue();

        lexer.getNextToken();

        if((label_started = tryToParseVarAssignment(label)) ||
           (label_started = tryToParseFuncCall(label)) )
        {
            return label_started;
        }
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseVarAssignment(const std::string& label) {
    if( lexer.getCurrentToken().getType() == TokenType::ASSIGN )
    {
        std::optional<Assignable *> assignable;

        lexer.getNextToken();

        if(!(assignable = tryToParseAssignable()))
        {
            throw std::runtime_error("var assignment invalid");
        }

        lexer.getNextToken();
        return new VariableAssignment(label, assignable.value() );
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseFuncCall(const std::string& label) {
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
            return new FunctionCall(label, arguments.value());
        else
            return new FunctionCall(label, Arguments());
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseWhileLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::WHILE )
    {
        std::optional<Assignable *> condition;

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

        std::optional<LanguageElement*> while_block;

        if( !(while_block = tryToParseBlock()) )
        {
            throw std::runtime_error("while_invalid");
        }

        return new WhileLoop(condition.value(), while_block.value());
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseForEachLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::FOR )
    {
        std::string element_label;
        std::string container_label;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN ||
            lexer.getNextToken().getType() != TokenType::LABEL)
        {
            throw std::runtime_error("for invalid");
        }

        element_label = lexer.getCurrentToken().getLiteralValue();

        if( lexer.getNextToken().getType() != TokenType::COLON ||
            lexer.getNextToken().getType() != TokenType::LABEL)
        {
            throw std::runtime_error("for invalid");
        }

        container_label = lexer.getCurrentToken().getLiteralValue();

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("for invalid");
        }

        lexer.getNextToken();

        std::optional<LanguageElement*> for_statements;

        if( !(for_statements = tryToParseBlock()) )
        {
            throw std::runtime_error("for invalid");
        }

        return new ForEachLoop(element_label, container_label, for_statements.value());
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseRepeatLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::REPEAT )
    {
        std::optional<Assignable *> number_of_repeats;

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

        std::optional<LanguageElement*> repeat_statements;

        if( !(repeat_statements = tryToParseBlock()) )
        {
            throw std::runtime_error("repeat loop invalid");
        }

        return new RepeatLoop(number_of_repeats.value(), repeat_statements.value());
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseReturn() {
    if( lexer.getCurrentToken().getType() == TokenType::RETURN )
    {
        std::optional<LanguageElement*> return_statement;
        lexer.getNextToken();
        std::optional<Assignable *> return_value = tryToParseAssignable();
        if( !return_value )
        {
            throw std::runtime_error("return invalid");
        }
        lexer.getNextToken();
        return new Return(return_value.value());
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseAssignable() {
    std::optional<Assignable*> assignable;

    if(( assignable = tryToParseList() ) ||
       ( assignable = tryToParseOrCondition() ) ||
       ( assignable = tryToParseString() ) )
    {
        return assignable;
    }

    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseAdditiveExpression() {
    // additive = multiply, { addoperator, multiply }
    if( std::optional<Assignable*> multiply_expression = tryToParseMultiplyExpression() )
    {
        std::vector<Assignable*> expressions;
        std::vector<AdditiveOperator> operators;

        expressions.push_back(multiply_expression.value());

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

            expressions.push_back(multiply_expression.value());
        }

        return new AdditiveExpression(expressions, operators );
    }

    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseMultiplyExpression() {
    // multiply = element, { muloperator, element }
    if( std::optional<Assignable*> math_element = tryToParseMathElement() )
    {
        std::vector<Assignable*> elements;
        std::vector<MultiplyOperator> operators;

        elements.push_back(math_element.value());

        while( lexer.getCurrentToken().getType() == TokenType::MULTIPLY ||
               lexer.getCurrentToken().getType() == TokenType::DIVIDE )
        {
            if( lexer.getCurrentToken().getType() == TokenType::MULTIPLY )
            {
                operators.emplace_back(OperationType::MULTIPLY);
            }
            else
            {
                operators.emplace_back(OperationType::DIVIDE);
            }

            lexer.getNextToken();

            if( !(math_element = tryToParseMathElement()) )
            {
                throw std::runtime_error("multiply expression invalid");
            }

            elements.push_back(math_element.value());
        }

        return new MultiplyExpression( elements, operators );
    }

    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseMathElement() {
    bool is_negated = false;
    Assignable * result = nullptr;

    if( lexer.getCurrentToken().getType() == TokenType::MINUS )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::NUMBER )
    {
        lexer.getNextToken();
        result = new Number(lexer.getCurrentToken().getNumericValue());
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::LABEL )
    {
        std::string label = lexer.getCurrentToken().getLiteralValue();

        lexer.getNextToken();

        if( std::optional<LanguageElement*> func_call = tryToParseFuncCall(label)) {
            result = dynamic_cast<Assignable*>(func_call.value());
        }
        else
        {
            result = new Label( label );
        }
    }
    else if( std::optional<Assignable*> parent_expr = tryToParseParentExpression() )
    {
        result = parent_expr.value();
    }

    if( result != nullptr )
    {
        if( is_negated )
        {
            return new NegatedMathElement(result);
        }
        return result;
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseList() {
    if ( lexer.getCurrentToken().getType() == TokenType::BRACKET_OPEN )
    {
        std::vector<Assignable*> elements;
        lexer.getNextToken();
        if( std::optional<Assignable*> elem = tryToParseAssignable() )
        {
            elements.push_back(elem.value());
            while( lexer.getCurrentToken().getType() == TokenType::COMMA )
            {
                lexer.getNextToken();
                if( (elem = tryToParseAssignable()) )
                {
                    elements.push_back(elem.value());
                }
                else
                {
                    throw std::runtime_error("elements invalid");
                }
            }
            return new List( elements );
        }
    }
    return std::nullopt;
}

std::optional<Arguments> Parser::tryToParseArguments() {
    if( std::optional<Assignable*> arg = tryToParseAssignable() )
    {
        std::vector<Assignable*> args;
        args.push_back(arg.value());
        while( lexer.getCurrentToken().getType() == TokenType::COMMA )
        {
            lexer.getNextToken();
            if( (arg = tryToParseAssignable()) )
            {
                args.push_back(arg.value());
            }
            else
            {
                throw std::runtime_error("args invalid");
            }
        }
        return Arguments( args );
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseParentExpression() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
        if ( std::optional<Assignable*> expr = tryToParseAdditiveExpression() )
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

std::optional<Assignable *> Parser::tryToParseString() {
    if( lexer.getCurrentToken().getType() == TokenType::STRING )
    {
        auto str = new String( lexer.getCurrentToken().getLiteralValue() );
        lexer.getNextToken();
        return str;
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseOrCondition() {
    // condition = andCond, { orOp, andCond }
    if( std::optional<Assignable*> condition = tryToParseAndCondition() )
    {
        std::vector<Assignable*> conditions;

        conditions.push_back(condition.value());

        while( lexer.getCurrentToken().getType() == TokenType::OR_SYMBOLIC ||
               lexer.getCurrentToken().getType() == TokenType::OR )
        {
            lexer.getNextToken();
            if( (condition = tryToParseAndCondition()) )
            {
                conditions.push_back(condition.value());
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return new OrCondition( conditions );
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseAndCondition() {
    // and_condition = eqCond, { andOp, eqCond }
    if( std::optional<Assignable*> condition = tryToParseEqualityCondition() )
    {
        std::vector<Assignable*> conditions;

        conditions.push_back(condition.value());

        while( lexer.getCurrentToken().getType() == TokenType::AND_SYMBOLIC ||
               lexer.getCurrentToken().getType() == TokenType::AND )
        {
            lexer.getNextToken();
            if( (condition = tryToParseEqualityCondition()) )
            {
                conditions.push_back(condition.value());
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }
        return new AndCondition( conditions );
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseEqualityCondition() {
    // eq_cond = relational_cond, [ eqOP, relational_cond ]
    if( std::optional<Assignable*> first_condition = tryToParseRelationalCondition() )
    {

        if( lexer.getCurrentToken().getType() == TokenType::EQUAL ||
            lexer.getCurrentToken().getType() == TokenType::NOT_EQUAL )
        {
            bool equals = lexer.getCurrentToken().getType() == TokenType::EQUAL;

            lexer.getNextToken();

            if( std::optional<Assignable*> second_condition = tryToParseRelationalCondition() )
            {
                return new EqualityCondition(
                        first_condition.value(),
                        equals,
                        second_condition.value()
                );
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return new EqualityCondition( first_condition.value() );
    }
    return std::nullopt;
}

std::optional<Assignable *> Parser::tryToParseRelationalCondition() {
    bool is_negated = false;
    std::optional<Assignable*> result = std::nullopt;

    if( lexer.getCurrentToken().getType() == TokenType::NEGATION )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::FALSE )
    {
        lexer.getNextToken();
        result = new Bool(false);
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::TRUE )
    {
        lexer.getNextToken();
        result = new Bool( true);
    }
    else if ( std::optional<Assignable*> comparison = tryToParseComparison() )
    {
        result = comparison.value();
    }
    else if( std::optional<Assignable*> parent_condition = tryToParseParentCondition() )
    {
        result = parent_condition.value();
    }

    if( is_negated && result != std::nullopt )
    {
        return new NegatedLogicalElement( result.value() );
    }
    return result;
}

std::optional<Assignable *> Parser::tryToParseParentCondition() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
        if ( std::optional<Assignable*> cond = tryToParseOrCondition() )
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

std::optional<Assignable *> Parser::tryToParseComparison() {
    if( std::optional<Assignable*> first_element = tryToParseAdditiveExpression() )
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

            if( std::optional<Assignable*> second_element = tryToParseAdditiveExpression() )
            {
                return new Comparison(first_element.value(), relation, second_element.value());
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return new Comparison( first_element.value() );
    }
    return std::nullopt;
}

