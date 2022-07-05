#include "Return.h"
#include "LanguageElementVisitor.h"

void Return::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::unique_ptr<Assignable> & Return::getValue() const {
    return value;
}
