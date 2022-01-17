#include "FunctionCall.h"
#include "LanguageElementVisitor.h"
#include "Variables/Evaluator.h"

void FunctionCall::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}

void FunctionCall::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::string &FunctionCall::getName() const {
    return name;
}

const Arguments &FunctionCall::getArguments() const {
    return arguments;
}
