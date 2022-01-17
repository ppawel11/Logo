#include "EqualityCondition.h"
#include "../Variables/Evaluator.h"

void EqualityCondition::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::unique_ptr<Assignable> & EqualityCondition::getFirstCondition() const {
    return first_condition;
}

const std::optional<std::unique_ptr<Assignable>> & EqualityCondition::getSecondCondition() const {
    return second_condition;
}

const std::optional<bool> &EqualityCondition::getEquals() const {
    return equals;
}
