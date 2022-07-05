#include "WhileLoop.h"
#include "LanguageElementVisitor.h"

void WhileLoop::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::unique_ptr<Assignable> & WhileLoop::getCondition() const {
    return condition;
}

const std::unique_ptr<LanguageElement> & WhileLoop::getLoop() const {
    return loop;
}
