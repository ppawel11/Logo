#include "WhileLoop.h"
#include "../../Interpreter/Interpreter.h"

void WhileLoop::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

Assignable *WhileLoop::getCondition() const {
    return condition;
}

LanguageElement *WhileLoop::getLoop() const {
    return loop;
}
