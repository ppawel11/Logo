#include "MultiplyExpression.h"
#include "../../../Interpreter/Interpreter.h"

void MultiplyExpression::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<Assignable *> &MultiplyExpression::getElements() const {
    return elements;
}

const std::vector<MultiplyOperator> &MultiplyExpression::getOperators() const {
    return operators;
}
