#include "ListOfAssignable.h"
#include "Variables/Evaluator.h"

void ListOfAssignable::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate( this );
}

const std::vector<std::unique_ptr<Assignable>> & ListOfAssignable::get_elements() {
    return elements;
}
