#include "NegatedMathElement.h"
#include "../Variables/Evaluator.h"

void NegatedMathElement::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::unique_ptr<Assignable> & NegatedMathElement::getElement() const {
    return element;
}
