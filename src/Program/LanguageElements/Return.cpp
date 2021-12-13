#include "Return.h"
#include "../../Interpreter/Interpreter.h"

void Return::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

Assignable *Return::getValue() const {
    return value;
}
