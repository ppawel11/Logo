#include "AdditiveExpression.h"
#include "../../../Interpreter/Interpreter.h"

void AdditiveExpression::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<Assignable *> &AdditiveExpression::getExpressions() const {
    return expressions;
}

const std::vector<AdditiveOperator> &AdditiveExpression::getOperators() const {
    return operators;
}
