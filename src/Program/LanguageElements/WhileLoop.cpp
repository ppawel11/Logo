#include "WhileLoop.h"
#include "../../Interpreter/Interpreter.h"

void WhileLoop::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::unique_ptr<Assignable> & WhileLoop::getCondition() const {
    return condition;
}

const std::unique_ptr<LanguageElement> & WhileLoop::getLoop() const {
    return loop;
}
