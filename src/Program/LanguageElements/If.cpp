#include "If.h"
#include "../../Interpreter/Interpreter.h"

void If::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

LanguageElement *If::getIfBlock() const {
    return if_block;
}

const std::optional<LanguageElement *> &If::getElseBlock() const {
    return else_block;
}

Assignable *If::getCondition() const {
    return condition;
}
