#include "ForEachLoop.h"
#include "../../Interpreter/Interpreter.h"

void ForEachLoop::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

const std::string &ForEachLoop::getValueLabel() const {
    return value_label;
}

const std::string &ForEachLoop::getContainerLabel() const {
    return container_label;
}

const std::unique_ptr<LanguageElement> &ForEachLoop::getLoop() const {
    return loop;
}
