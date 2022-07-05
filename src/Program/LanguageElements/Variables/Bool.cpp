#include "Bool.h"
#include "Evaluator.h"
#include <system_error>

void Bool::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

bool Bool::isValue() const {
    return value;
}

void Bool::setValue(bool value) {
    Bool::value = value;
}
