#include "FunctionDefinition.h"
#include "../../Interpreter/Interpreter.h"

void FunctionDefinition::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}
