#include "NegatedLogicalElement.h"
#include "../Variables/Evaluator.h"

void NegatedLogicalElement::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::unique_ptr<Assignable> & NegatedLogicalElement::getElement() const {
    return element;
}
