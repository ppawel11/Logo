#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H

#include <utility>

#include <memory>
#include <optional>

#include "../Lexical/Lexer/Lexer.h"
#include "../Lexical/Token/Token.h"

#include "../Program/Program.h"
#include "../Program/Statement.h"
#include "../Program/LanguageElements/Arguments.h"
#include "../Program/LanguageElements/Variables/Assignable.h"
#include "../Program/LanguageElements/FunctionBody.h"
#include "../Program/LanguageElements/VariableAssignment.h"
#include "../Program/LanguageElements/FunctionCall.h"
#include "../Program/LanguageElements/Logical/OrCondition.h"
#include "../Program/LanguageElements/WhileLoop.h"
#include "../Program/LanguageElements/ForEachLoop.h"
#include "../Program/LanguageElements/Math/AdditiveExpression.h"
#include "../Program/LanguageElements/RepeatLoop.h"
#include "../Program/LanguageElements/Math/MathElement.h"
#include "../Program/LanguageElements/If.h"
#include "../Program/LanguageElements/VariableDeclaration.h"
#include "../Program/LanguageElements/Return.h"
#include "../Program/LanguageElements/Variables/List.h"
#include "../Program/LanguageElements/Variables/String.h"
#include "../Program/LanguageElements/Block.h"
#include "../Program/LanguageElements/FunctionDefinition.h"


class Parser {
    Lexer lexer;

public:
    explicit Parser(Lexer lex): lexer{ std::move(lex) } {}

    Program parseProgram();

private:
    std::optional<FunctionDefinition> tryToParseFuncDef();

    std::optional<LanguageElement *> tryToParseLaguageElement();

    std::optional<LanguageElement *> tryToParseSemicolonEnded();

    std::optional<LanguageElement *> tryToParseIf();

    std::optional<LanguageElement *> tryToParseLoop();

    std::optional<LanguageElement *> tryToParseVarDeclaration();

    std::optional<LanguageElement *> tryToParseVarAssignmentOrFuncCall();

    std::optional<LanguageElement *> tryToParseVarAssignment(const std::string& label);

    std::optional<LanguageElement *> tryToParseFuncCall(const std::string& label);

    std::optional<LanguageElement *> tryToParseWhileLoop();

    std::optional<LanguageElement *> tryToParseForEachLoop();

    std::optional<LanguageElement *> tryToParseRepeatLoop();

    std::optional<LanguageElement *> tryToParseReturn();

    std::optional<Assignable> tryToParseAssignable();

    std::optional<OrCondition> tryToParseCondition();

    std::optional<AdditiveExpression> tryToParseAdditiveExpression();

    std::optional<MultiplyExpression> tryToParseMultiplyExpression();

    std::optional<List> tryToParseList();

    std::optional<Block> tryToParseBlock();

    std::optional<MathElement> tryToParseMathElement();

    std::optional<Arguments> tryToParseArguments();

    std::optional<AdditiveExpression> tryToParseParentExpression();

    std::optional<Assignable> tryToParseLabelOrFunctionCall();

    std::optional<Assignable> tryToParseString();

    std::optional<AndCondition> tryToParseAndCondition();

    std::optional<EqualityCondition> tryToParseEqualityCondition();

    std::optional<RelationalCondition> tryToParseRelationalCondition();

    std::optional<OrCondition> tryToParseParentCondition();

    std::optional<Comparison> tryToParseComparison();
};


#endif //TKOM_PARSER_H
