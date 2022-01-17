#include "Backward.h"
#include "../../Program/LanguageElements/LanguageElementVisitor.h"

void Backward::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
