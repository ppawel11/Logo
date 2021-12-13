#ifndef TKOM_ORCONDITION_H
#define TKOM_ORCONDITION_H

#include <vector>
#include "AndCondition.h"
#include "../Variables/Assignable.h"

class OrCondition: public Assignable {
    // and_condition, { or_operator, and_condition }
    std::vector<Assignable*> elements;

public:
    explicit OrCondition( std::vector<Assignable*> elements_):
        elements{ std::move(elements_) },
        Assignable()
    {}

    const std::vector<Assignable *> &getElements() const;

    void be_evaluated(Interpreter *interpreter) override;
};


#endif //TKOM_ORCONDITION_H
