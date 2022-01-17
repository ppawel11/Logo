#include "AndCondition.h"
#include "../Variables/Evaluator.h"

void AndCondition::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::unique_ptr<Assignable>> & AndCondition::getEqConditions() const {
    return eq_conditions;
}
