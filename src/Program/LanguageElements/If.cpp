#include "If.h"
#include "../../Interpreter/Interpreter.h"

void If::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::unique_ptr<LanguageElement> & If::getIfBlock() const {
    return if_block;
}

const std::optional<std::unique_ptr<LanguageElement>> & If::getElseBlock() const {
    return else_block;
}

const std::unique_ptr<Assignable> & If::getCondition() const {
    return condition;
}
