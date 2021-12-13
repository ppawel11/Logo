#include "Label.h"
#include "../../../Interpreter/Interpreter.h"

void Label::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::string &Label::getLabel() const {
    return label;
}
