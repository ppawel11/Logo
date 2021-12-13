#include "MathElement.h"
#include "../../../Interpreter/Interpreter.h"

void MathElement::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

