#include "ForEachLoop.h"
#include "../../Interpreter/Interpreter.h"

void ForEachLoop::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}
