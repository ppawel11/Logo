#include "Forward.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Forward::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
