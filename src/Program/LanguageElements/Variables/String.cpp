#include "String.h"
#include "../../../Interpreter/Interpreter.h"

void String::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::string &String::getValue() const {
    return value;
}

void String::setValue(const std::string &value) {
    this->value = value;
}
