#include "List.h"
#include "../../../Interpreter/Interpreter.h"

void List::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<Assignable *> &List::get_elements() const {
    return elements;
}
