#include "Write.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Write::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
