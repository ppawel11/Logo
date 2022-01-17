#include "ForEachLoop.h"
#include "LanguageElementVisitor.h"

void ForEachLoop::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::string &ForEachLoop::getValueLabel() const {
    return value_label;
}

const std::unique_ptr<Assignable> & ForEachLoop::getContainer() const {
    return container;
}

const std::unique_ptr<LanguageElement> &ForEachLoop::getLoop() const {
    return loop;
}
