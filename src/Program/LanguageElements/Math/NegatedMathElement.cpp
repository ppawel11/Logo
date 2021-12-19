#include "NegatedMathElement.h"
#include "../../../Interpreter/Interpreter.h"

void NegatedMathElement::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

Assignable *NegatedMathElement::getElement() const {
    return element;
}
