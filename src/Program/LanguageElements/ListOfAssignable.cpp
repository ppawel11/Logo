#include "ListOfAssignable.h"
#include "../../Interpreter/Interpreter.h"

void ListOfAssignable::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate( this );
}

const std::vector<std::unique_ptr<Assignable>> & ListOfAssignable::get_elements() {
    return elements;
}
