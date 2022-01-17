#ifndef TKOM_ANDCONDITION_H
#define TKOM_ANDCONDITION_H

#include <utility>
#include <vector>
#include "EqualityCondition.h"

class AndCondition: public Assignable {
    // equality_condition, { and_operator, equality_condition }
    std::vector<std::unique_ptr<Assignable>> eq_conditions;
public:
    AndCondition(std::vector<std::unique_ptr<Assignable>> eq_conditions_) :
        eq_conditions{std::move(eq_conditions_ )}
    {}

    const std::vector<std::unique_ptr<Assignable>> & getEqConditions() const;

    void be_evaluated(Evaluator *interpreter) override;

};

#endif //TKOM_ANDCONDITION_H
