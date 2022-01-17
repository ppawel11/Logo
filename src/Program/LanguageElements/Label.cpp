#include "Label.h"
#include "Variables/Evaluator.h"

void Label::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate( this );
}

std::string Label::get_variable_name() {
    return variable_name;
}
