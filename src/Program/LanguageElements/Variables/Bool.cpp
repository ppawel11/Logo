#include "Bool.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Bool::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

bool Bool::isValue() const {
    return value;
}

void Bool::setValue(bool value) {
    Bool::value = value;
}
