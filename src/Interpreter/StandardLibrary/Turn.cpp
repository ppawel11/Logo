#include "Turn.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Turn::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
