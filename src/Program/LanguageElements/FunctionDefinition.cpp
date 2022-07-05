#include "FunctionDefinition.h"
#include "LanguageElementVisitor.h"

void FunctionDefinition::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}
