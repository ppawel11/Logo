#include "VariableAssignment.h"
#include "../../Interpreter/Interpreter.h"

void VariableAssignment::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::string &VariableAssignment::getLabel() const {
    return label;
}

const std::unique_ptr<Assignable> & VariableAssignment::getValue() const {
    return value;
}
