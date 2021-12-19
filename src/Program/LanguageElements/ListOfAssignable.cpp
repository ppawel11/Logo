#include "ListOfAssignable.h"
#include "../../Interpreter/Interpreter.h"

void ListOfAssignable::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate( this );
}

std::vector<Assignable *> ListOfAssignable::get_elements() {
    return elements;
}
