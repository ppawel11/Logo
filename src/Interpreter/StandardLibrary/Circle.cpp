#include "Circle.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Circle::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret(this);
}
