#include "Reset.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Reset::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
