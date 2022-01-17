#include "Read.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Read::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
