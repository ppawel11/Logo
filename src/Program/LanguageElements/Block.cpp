#include "Block.h"
#include "LanguageElementVisitor.h"

void Block::be_handled(LanguageElementVisitor *interpreter) {
    interpreter->interpret( this );
}
