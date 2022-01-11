#include "Block.h"
#include "../../Interpreter/Interpreter.h"

void Block::be_handled(Interpreter *interpreter) {
    interpreter->interpret( this );
}
