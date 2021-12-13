#include "OrCondition.h"
#include "../../../Interpreter/Interpreter.h"

void OrCondition::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<Assignable *> &OrCondition::getElements() const {
    return elements;
}
