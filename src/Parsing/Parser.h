#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H

#include <utility>

#include <memory>
#include <optional>

#include "../Lexical/Lexer/Lexer.h"
#include "../Lexical/Token/Token.h"

#include "../Program/Program.h"
#include "../Program/LanguageElements/Arguments.h"
#include "../Program/LanguageElements/Variables/Assignable.h"
#include "../Program/LanguageElements/FunctionBody.h"
#include "../Program/LanguageElements/VariableAssignment.h"
#include "../Program/LanguageElements/FunctionCall.h"
#include "../Program/LanguageElements/Logical/OrCondition.h"
#include "../Program/LanguageElements/WhileLoop.h"
#include "../Program/LanguageElements/ForEachLoop.h"
#include "../Program/LanguageElements/Math/AdditiveExpression.h"
#include "../Program/LanguageElements/Math/NegatedMathElement.h"
#include "../Program/LanguageElements/Logical/NegatedLogicalElement.h"
#include "../Program/LanguageElements/RepeatLoop.h"
#include "../Program/LanguageElements/Variables/Number.h"
#include "../Program/LanguageElements/Variables/Bool.h"
#include "../Program/LanguageElements/If.h"
#include "../Program/LanguageElements/VariableDeclaration.h"
#include "../Program/LanguageElements/Return.h"
#include "../Program/LanguageElements/ListOfAssignable.h"
#include "../Program/LanguageElements/Variables/String.h"
#include "../Program/LanguageElements/Block.h"
#include "../Program/LanguageElements/Logical/Comparison.h"
#include "../Program/LanguageElements/Label.h"
#include "../Program/LanguageElements/FunctionDefinition.h"
#include "../Program/LanguageElements/Logical/RelationType.h"

#include "../Parsing/Exceptions/ParserException.h"



class Parser {
    Lexer lexer;

public:
    explicit Parser(Lexer lex): lexer{ std::move(lex) } {}

    Program parseProgram();

private:
    std::optional<std::unique_ptr<FunctionDefinition>> tryToParseFuncDef();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseLanguageElement();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseSemicolonEnded();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseIf();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseLoop();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseVarDeclaration();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseVarAssignmentOrFuncCall();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseVarAssignment(const std::string& label);

    template<typename T> std::optional<std::unique_ptr<T>> tryToParseFuncCall(const std::string& label);

    std::optional<std::unique_ptr<LanguageElement>> tryToParseWhileLoop();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseForEachLoop();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseRepeatLoop();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseReturn();

    std::optional<std::unique_ptr<LanguageElement>> tryToParseBlock();

    std::optional<Arguments> tryToParseArguments();

    std::optional<std::unique_ptr<Assignable>> tryToParseAssignable();

    std::optional<std::unique_ptr<Assignable>> tryToParseOrCondition();

    std::optional<std::unique_ptr<Assignable>> tryToParseAdditiveExpression();

    std::optional<std::unique_ptr<Assignable>> tryToParseMultiplyExpression();

    std::optional<std::unique_ptr<Assignable>> tryToParseList();

    std::optional<std::unique_ptr<Assignable>> tryToParseMathElement();

    std::optional<std::unique_ptr<Assignable>> tryToParseParentExpression();

    std::optional<std::unique_ptr<Assignable>> tryToParseString();

    std::optional<std::unique_ptr<Assignable>> tryToParseAndCondition();

    std::optional<std::unique_ptr<Assignable>> tryToParseEqualityCondition();

    std::optional<std::unique_ptr<Assignable>> tryToParseRelationalCondition();

    std::optional<std::unique_ptr<Assignable>> tryToParseParentCondition();

    std::optional<std::unique_ptr<Assignable>> tryToParseComparison();
};


#endif //TKOM_PARSER_H
