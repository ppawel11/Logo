#include "VariableAssignment.h"
#include "LanguageElementVisitor.h"

void VariableAssignment::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::string &VariableAssignment::getLabel() const {
    return label;
}

const std::unique_ptr<Assignable> & VariableAssignment::getValue() const {
    return value;
}
