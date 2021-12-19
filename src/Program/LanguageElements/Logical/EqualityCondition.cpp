#include "EqualityCondition.h"
#include "../../../Interpreter/Interpreter.h"

void EqualityCondition::be_evaluated(Interpreter *interpreter) {
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
