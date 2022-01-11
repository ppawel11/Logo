#include "Number.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Number::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

int Number::getValue() const {
    return value;
}

void Number::setValue(int value) {
    Number::value = value;
}
