#include "Label.h"
#include "../../Interpreter/Interpreter.h"

void Label::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate( this );
}

std::string Label::get_variable_name() {
    return variable_name;
}
