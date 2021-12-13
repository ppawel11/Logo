#include "AndCondition.h"
#include "../../../Interpreter/Interpreter.h"

void AndCondition::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<Assignable *> &AndCondition::getEqConditions() const {
    return eq_conditions;
}
