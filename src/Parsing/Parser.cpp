#include "Parser.h"


Program Parser::parseProgram() {
    std::vector<LanguageElement*> statements;
    std::map<std::string, FunctionDefinition> func_definitions;

    std::optional<LanguageElement*> lang_element;
    std::optional<FunctionDefinition> func_definition;

    lexer.getNextToken();
    while(
            (lang_element = tryToParseLaguageElement()) ||
            (func_definition = tryToParseFuncDef())
         )
    {
        if( lang_element )
        {
            statements.push_back(lang_element.value());
        }
        else
        {
            func_definitions.insert( std::pair<std::string, FunctionDefinition>(func_definition.value().getName(), func_definition.value()));
        }
    }

    return Program( statements, func_definitions );
}

std::optional<LanguageElement *> Parser::tryToParseLaguageElement() {
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

        if( lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("func def invalid");
        }

        lexer.getNextToken();

        std::optional<Block> func_body = tryToParseBlock();

        if ( !(func_body) )
        {
            throw std::runtime_error("func def invalid");
        }

        return FunctionDefinition(func_name, parameters, func_body.value());
    }

    return std::nullopt;
}

std::optional<Block> Parser::tryToParseBlock() {
    if (lexer.getCurrentToken().getType() == TokenType::CURLY_BRACKET_OPEN)
    {
        lexer.getNextToken();

        std::optional<LanguageElement*> statement;
        std::vector<LanguageElement*> statement_vec;

        while ((statement = tryToParseLaguageElement())) {
            statement_vec.push_back(statement.value());
        }

        if (lexer.getCurrentToken().getType() != TokenType::CURLY_BRACKET_CLOSE )
        {
            throw std::runtime_error("block invalid");
        }
        lexer.getNextToken();

        return std::optional<Block>(Block(statement_vec));
    }
    return std::nullopt;
}

std::optional<LanguageElement *> Parser::tryToParseIf() {
    if( lexer.getCurrentToken().getType() == TokenType::IF )
    {
        std::optional<OrCondition> condition;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("if invalid");
        }

        lexer.getNextToken();

        if(!(condition = tryToParseCondition()) ||
            lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("if invalid");
        }

        lexer.getNextToken();

        std::optional<Block> if_statement;
        std::optional<Block> else_statement;

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

        std::optional<Assignable> value = tryToParseAssignable();

        if( !value )
        {
            throw std::runtime_error("var declaration invalid");
        }

        return new VariableDeclaration();
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
        std::optional<Assignable> assignable;

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
        // func_call = label, (, [ arguments ], )
        // arguments = assignable,  { ',' , assignable }

        if( lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("func call arguments invalid");
        }

        lexer.getNextToken();

        if( arguments )
            return new FunctionCall(label, arguments.value());
        else
            return new FunctionCall(label, Arguments({}));
    }

    return std::nullopt;
}

std::optional<LanguageElement*> Parser::tryToParseWhileLoop() {
    if( lexer.getCurrentToken().getType() == TokenType::WHILE )
    {
        std::optional<OrCondition> condition;

        if( lexer.getNextToken().getType() != TokenType::PARENTHESIS_OPEN )
        {
            throw std::runtime_error("while invalid");
        }

        lexer.getNextToken();

        if(!(condition = tryToParseCondition()) ||
            lexer.getCurrentToken().getType() != TokenType::PARENTHESIS_CLOSE )
        {
            throw std::runtime_error("while invalid");
        }

        lexer.getNextToken();

        std::optional<Block> while_block;

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

        std::optional<Block> for_statements;

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
        std::optional<AdditiveExpression> number_of_repeats;

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

        std::optional<Block> repeat_statements;

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
        std::optional<Assignable> return_value = tryToParseAssignable();
        if( !return_value )
        {
            throw std::runtime_error("return invalid");
        }
        lexer.getNextToken();
        return new Return(return_value.value());
    }
    return std::nullopt;
}

std::optional<Assignable> Parser::tryToParseAssignable() {
    std::optional<Assignable> assignable;

    if(( assignable = tryToParseList() ) ||
       ( assignable = tryToParseAdditiveExpression() ) ||
       ( assignable = tryToParseString() ) )
    {
        return assignable;
    }

    return std::nullopt;
}

std::optional<AdditiveExpression> Parser::tryToParseAdditiveExpression() {
    // additive = multiply, { addoperator, multiply }
    if( std::optional<MultiplyExpression> multiply_expression = tryToParseMultiplyExpression() )
    {
        std::vector<MultiplyExpression> expressions;
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

        return AdditiveExpression(expressions, operators );
    }

    return std::nullopt;
}

std::optional<MultiplyExpression> Parser::tryToParseMultiplyExpression() {
    // multipy = element, { muloperator, element }
    if( std::optional<MathElement> math_element = tryToParseMathElement() )
    {
        std::vector<MathElement> elements;
        std::vector<MultiplyOperator> operators;

        elements.push_back(std::move(math_element.value()));

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
                throw std::runtime_error("parsing expression invalid");
            }

            elements.push_back(math_element.value());
        }

        return MultiplyExpression( elements, operators );
    }

    return std::nullopt;
}

std::optional<MathElement> Parser::tryToParseMathElement() {
    std::optional<MathElement> element;
    bool is_negated = false;

    if( lexer.getCurrentToken().getType() == TokenType::MINUS )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::NUMBER )
    {
        lexer.getNextToken();
        return MathElement(lexer.getCurrentToken().getNumericValue(), is_negated);
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::LABEL )
    {
        std::string label = lexer.getCurrentToken().getLiteralValue();

        lexer.getNextToken();

        if( std::optional<LanguageElement*> func_call = tryToParseFuncCall(label)) {
            return MathElement(*reinterpret_cast<FunctionCall*>(func_call.value()), is_negated);
        }
        else
        {
            return MathElement( label, is_negated );
        }
    }
    else if( std::optional<AdditiveExpression> parent_expr = tryToParseParentExpression() )
    {
        return MathElement(new AdditiveExpression(parent_expr.value()), is_negated );
    }

    return std::nullopt;
}

std::optional<List> Parser::tryToParseList() {
    if ( lexer.getCurrentToken().getType() == TokenType::BRACKET_OPEN )
    {
        std::vector<Assignable> elements;
        lexer.getNextToken();
        if( std::optional<Assignable> elem = tryToParseAssignable() )
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
            return List( elements );
        }
        throw std::runtime_error("elements invalid");
    }
    return std::nullopt;
}

std::optional<Arguments> Parser::tryToParseArguments() {
    if( std::optional<Assignable> arg = tryToParseAssignable() )
    {
        std::vector<Assignable> args;
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

std::optional<AdditiveExpression> Parser::tryToParseParentExpression() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
        if ( std::optional<AdditiveExpression> expr = tryToParseAdditiveExpression() )
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

std::optional<Assignable> Parser::tryToParseString() {
    if( lexer.getCurrentToken().getType() == TokenType::STRING )
    {
        String str = String( lexer.getCurrentToken().getLiteralValue() );
        lexer.getNextToken();
        return str;
    }
    return std::nullopt;
}

std::optional<OrCondition> Parser::tryToParseCondition() {
    // condition = andCond, { orOp, andCond }
    if( std::optional<AndCondition> condition = tryToParseAndCondition() )
    {
        std::vector<AndCondition> conditions;

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

        return OrCondition( conditions );
    }
    return std::nullopt;
}

std::optional<AndCondition> Parser::tryToParseAndCondition() {
    // and_condition = eqCond, { andOp, eqCond }
    if( std::optional<EqualityCondition> condition = tryToParseEqualityCondition() )
    {
        std::vector<EqualityCondition> conditions;

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
        return AndCondition( conditions );
    }
    return std::nullopt;
}

std::optional<EqualityCondition> Parser::tryToParseEqualityCondition() {
    // eq_cond = relatinal_cond, [ eqOP, relational_cond ]
    if( std::optional<RelationalCondition> first_condition = tryToParseRelationalCondition() )
    {

        if( lexer.getCurrentToken().getType() == TokenType::EQUAL ||
            lexer.getCurrentToken().getType() == TokenType::NOT_EQUAL )
        {
            bool equals = lexer.getCurrentToken().getType() == TokenType::EQUAL;

            lexer.getNextToken();

            if( std::optional<RelationalCondition> second_condition = tryToParseRelationalCondition() )
            {
                return EqualityCondition(
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

        return EqualityCondition( std::move(first_condition.value()) );
    }
    return std::nullopt;
}

std::optional<RelationalCondition> Parser::tryToParseRelationalCondition() {
    bool is_negated = false;

    if( lexer.getCurrentToken().getType() == TokenType::NEGATION )
    {
        is_negated = true;
        lexer.getNextToken();
    }

    if( lexer.getCurrentToken().getType() == TokenType::FALSE )
    {
        lexer.getNextToken();
        return RelationalCondition(is_negated, false);
    }
    else if ( lexer.getCurrentToken().getType() == TokenType::TRUE )
    {
        lexer.getNextToken();
        return RelationalCondition(is_negated, true);
    }
    else if ( std::optional<Comparison> comparison = tryToParseComparison() )
    {
        return RelationalCondition( is_negated, comparison.value() );
    }
    else if( std::optional<OrCondition> parent_condition = tryToParseParentCondition() )
    {
        return RelationalCondition(is_negated, new OrCondition(parent_condition.value()) );
    }

    return std::nullopt;
}

std::optional<OrCondition> Parser::tryToParseParentCondition() {
    if( lexer.getCurrentToken().getType() == TokenType::PARENTHESIS_OPEN )
    {
        lexer.getNextToken();
        if ( std::optional<OrCondition> cond = tryToParseCondition() )
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

std::optional<Comparison> Parser::tryToParseComparison() {
    if( std::optional<AdditiveExpression> first_element = tryToParseAdditiveExpression() )
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

            if( std::optional<AdditiveExpression> second_element = tryToParseAdditiveExpression() )
            {
                return Comparison(first_element.value(), relation, second_element.value());
            }
            else
            {
                throw std::runtime_error("condition parse invalid");
            }
        }

        return Comparison( first_element.value() );
    }
    return std::nullopt;
}

