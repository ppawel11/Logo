#include "String.h"
#include "../Variables/Evaluator.h"

void String::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::string &String::getValue() const {
    return value;
}

void String::setValue(const std::string &value) {
    this->value = value;
}
