#ifndef TKOM_EVALUATOR_H
#define TKOM_EVALUATOR_H

class AndCondition;
class OrCondition;
class Comparison;
class EqualityCondition;
class AdditiveExpression;
class MultiplyExpression;
class FunctionCall;
class Bool;
class String;
class Number;
class ListOfVariantValues;
class ListOfAssignable;
class Label;
class NegatedMathElement;
class NegatedLogicalElement;

class Evaluator {
public:
    virtual void evaluate(AndCondition * and_condition) = 0;
    virtual void evaluate(OrCondition * or_condition) = 0;
    virtual void evaluate(Comparison * comparison) = 0;
    virtual void evaluate(EqualityCondition * equality_condition) = 0;
    virtual void evaluate(AdditiveExpression * additive_expression) = 0;
    virtual void evaluate(MultiplyExpression * multiply_expression) = 0;
    virtual void evaluate(FunctionCall * function_call) = 0;
    virtual void evaluate(Bool * bool_val) = 0;
    virtual void evaluate(String * string_val) = 0;
    virtual void evaluate(Number * num_val) = 0;
    virtual void evaluate(ListOfVariantValues * list_val) = 0;
    virtual void evaluate(ListOfAssignable * list_val) = 0;
    virtual void evaluate(Label * label_val) = 0;
    virtual void evaluate(NegatedMathElement * negated_math_element) = 0;
    virtual void evaluate(NegatedLogicalElement * negated_logical_element) = 0;
};
#endif //TKOM_EVALUATOR_H
