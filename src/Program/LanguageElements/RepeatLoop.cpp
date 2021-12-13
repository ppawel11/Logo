#include "RepeatLoop.h"
#include "../../Interpreter/Interpreter.h"

void RepeatLoop::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

Assignable *RepeatLoop::getRepeats() const {
    return repeats;
}

LanguageElement *RepeatLoop::getLoop() const {
    return loop;
}
