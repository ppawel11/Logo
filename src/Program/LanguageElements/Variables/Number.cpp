#include "Number.h"
#include "../Variables/Evaluator.h"
#include <system_error>

void Number::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

int Number::getValue() const {
    return value;
}

void Number::setValue(int value) {
    Number::value = value;
}
