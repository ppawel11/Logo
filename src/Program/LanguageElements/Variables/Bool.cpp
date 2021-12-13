#include "Bool.h"
#include "../../../Interpreter/Interpreter.h"

void Bool::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

bool Bool::get_value() const {
    return value;
}
