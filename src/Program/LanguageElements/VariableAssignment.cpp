#include "VariableAssignment.h"
#include "../../Interpreter/Interpreter.h"

void VariableAssignment::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::string &VariableAssignment::getLabel() const {
    return label;
}

Assignable *VariableAssignment::getValue() const {
    return value;
}
