#ifndef TKOM_ORCONDITION_H
#define TKOM_ORCONDITION_H

#include <vector>
#include "AndCondition.h"
#include "../Variables/Assignable.h"

class OrCondition: public Assignable {
    // and_condition, { or_operator, and_condition }
    std::vector<std::unique_ptr<Assignable>> elements;

public:
    explicit OrCondition( std::vector<std::unique_ptr<Assignable>> elements_):
        elements{ std::move(elements_) },
        Assignable()
    {}

    const std::vector<std::unique_ptr<Assignable>> & getElements() const;

    void be_evaluated(Evaluator *interpreter) override;
};


#endif //TKOM_ORCONDITION_H
