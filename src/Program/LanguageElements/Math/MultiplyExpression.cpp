#include "MultiplyExpression.h"
#include "../Variables/Evaluator.h"

void MultiplyExpression::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::unique_ptr<Assignable>> & MultiplyExpression::getElements() const {
    return elements;
}

const std::vector<MultiplyOperator> &MultiplyExpression::getOperators() const {
    return operators;
}
