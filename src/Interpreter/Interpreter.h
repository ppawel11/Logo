#ifndef TKOM_INTERPRETER_H
#define TKOM_INTERPRETER_H

#include <utility>

#include "ScopeStack.h"
#include "../Program/Program.h"
#include "../Program/LanguageElements/ForEachLoop.h"
#include "../Program/LanguageElements/FunctionCall.h"
#include "../Program/LanguageElements/If.h"
#include "../Program/LanguageElements/RepeatLoop.h"
#include "../Program/LanguageElements/Return.h"
#include "../Program/LanguageElements/VariableAssignment.h"
#include "../Program/LanguageElements/VariableDeclaration.h"
#include "../Program/LanguageElements/WhileLoop.h"
#include "../Program/LanguageElements/Label.h"
#include "../Program/LanguageElements/ListOfAssignable.h"
#include "../Program/LanguageElements/Math/NegatedMathElement.h"
#include "../Program/LanguageElements/Logical/NegatedLogicalElement.h"
#include "../Program/LanguageElements/Logical/Comparison.h"

class Interpreter {
    ScopeStack scope_stack;
public:
    explicit Interpreter( ) = default;

    void interpret(const Program& program);

    void interpret(ForEachLoop * for_each_loop);
    void interpret(FunctionCall * function_call);
    void interpret(FunctionDefinition * function_definition);
    void interpret(If * if_statement);
    void interpret(RepeatLoop * repeat_loop);
    void interpret(WhileLoop * while_loop);
    void interpret(Return * return_statement);
    void interpret(VariableAssignment * variable_assignment);
    void interpret(VariableDeclaration * variable_declaration);
    void interpret(Block * block);

    void evaluate(AndCondition * and_condition);
    void evaluate(OrCondition * or_condition);
    void evaluate(Comparison * comparison);
    void evaluate(EqualityCondition * equality_condition);
    void evaluate(AdditiveExpression * additive_expression);
    void evaluate(MultiplyExpression * multiply_expression);
    void evaluate(FunctionCall * function_call);
    void evaluate(Bool * bool_val);
    void evaluate(String * string_val);
    void evaluate(Number * num_val);
    void evaluate(ListOfVariantValues * list_val);
    void evaluate(ListOfAssignable * list_val);
    void evaluate(Label * label_val);
    void evaluate(NegatedMathElement * negated_math_element);
    void evaluate(NegatedLogicalElement * negated_logical_element);
};


#endif //TKOM_INTERPRETER_H
