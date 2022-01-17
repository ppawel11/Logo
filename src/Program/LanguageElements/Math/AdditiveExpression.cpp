#include "AdditiveExpression.h"
#include "../Variables/Evaluator.h"

void AdditiveExpression::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::unique_ptr<Assignable>> & AdditiveExpression::getExpressions() const {
    return expressions;
}

const std::vector<AdditiveOperator> &AdditiveExpression::getOperators() const {
    return operators;
}
