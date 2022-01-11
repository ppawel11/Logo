#ifndef TKOM_LISTOFVARIANTVALUES_H
#define TKOM_LISTOFVARIANTVALUES_H

#include "Assignable.h"
#include "VariantValue.h"
#include "Number.h"
#include "Bool.h"
#include "String.h"

#include <utility>
#include <vector>

class ListOfVariantValues: public Assignable {
    std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> elements;

public:
    ListOfVariantValues(): elements{} {};

    const std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> &getElements() const;

    void setElements(const std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> &elements);

    explicit ListOfVariantValues( std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> elements) : elements{std::move(elements )} {}
    ~ListOfVariantValues() = default;
    void be_evaluated(Interpreter *interpreter) override;
};


#endif //TKOM_LISTOFVARIANTVALUES_H
