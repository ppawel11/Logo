#include "VariableDeclaration.h"
#include "../../Interpreter/Interpreter.h"

void VariableDeclaration::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::string &VariableDeclaration::getLabel() const {
    return label;
}

const std::unique_ptr<Assignable> & VariableDeclaration::getValue() const {
    return value;
}
