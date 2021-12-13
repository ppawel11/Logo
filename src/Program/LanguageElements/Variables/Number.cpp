#include "Number.h"
#include "../../../Interpreter/Interpreter.h"

void Number::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

int Number::get_value() const {
    return value;
}
