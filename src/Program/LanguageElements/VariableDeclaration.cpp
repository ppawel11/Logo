#include "VariableDeclaration.h"
#include "LanguageElementVisitor.h"

void VariableDeclaration::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::string &VariableDeclaration::getLabel() const {
    return label;
}

const std::unique_ptr<Assignable> & VariableDeclaration::getValue() const {
    return value;
}
