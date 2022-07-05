#include "Switch.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Switch::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
