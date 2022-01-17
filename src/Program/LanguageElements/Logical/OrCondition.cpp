#include "OrCondition.h"
#include "../Variables/Evaluator.h"

void OrCondition::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::unique_ptr<Assignable>> & OrCondition::getElements() const {
    return elements;
}
