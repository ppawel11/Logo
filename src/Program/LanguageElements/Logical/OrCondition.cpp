#include "OrCondition.h"
#include "../../../Interpreter/Interpreter.h"

void OrCondition::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::unique_ptr<Assignable>> & OrCondition::getElements() const {
    return elements;
}
