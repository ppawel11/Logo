#include "Clear.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Clear::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}
