#include "String.h"
#include "../../../Interpreter/Interpreter.h"

void String::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::string &String::get_value() const {
    return <#initializer#>;
}
