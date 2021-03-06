#include "RepeatLoop.h"
#include "LanguageElementVisitor.h"

void RepeatLoop::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

const std::unique_ptr<Assignable> & RepeatLoop::getRepeats() const {
    return repeats;
}

const std::unique_ptr<LanguageElement> & RepeatLoop::getLoop() const {
    return loop;
}
