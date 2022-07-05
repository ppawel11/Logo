#include "ListOfVariantValues.h"
#include "../Variables/Evaluator.h"

void ListOfVariantValues::be_evaluated(Evaluator *interpreter) {
    interpreter->evaluate(this);
}

const std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> &ListOfVariantValues::getElements() const {
    return elements;
}

void
ListOfVariantValues::setElements(const std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> &elements) {
    ListOfVariantValues::elements = elements;
}
