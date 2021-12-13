#include "FunctionCall.h"
#include "../../Interpreter/Interpreter.h"

void FunctionCall::be_handled(Interpreter *interpreter) {
    interpreter->interpret(this);
}

void FunctionCall::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::string &FunctionCall::getName() const {
    return name;
}

const Arguments &FunctionCall::getArguments() const {
    return arguments;
}
