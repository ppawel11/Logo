#include "NegatedLogicalElement.h"
#include "../../../Interpreter/Interpreter.h"

void NegatedLogicalElement::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

Assignable *NegatedLogicalElement::getElement() const {
    return element;
}
