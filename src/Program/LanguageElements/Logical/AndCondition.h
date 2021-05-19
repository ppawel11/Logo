#ifndef TKOM_ANDCONDITION_H
#define TKOM_ANDCONDITION_H

#include <utility>
#include <vector>
#include "EqualityCondition.h"

class AndCondition {
    std::vector<EqualityCondition> eq_conditions;
public:
    AndCondition(std::vector<EqualityCondition> eq_conditions_) :
        eq_conditions{std::move(eq_conditions_ )}
    {}
};


#endif //TKOM_ANDCONDITION_H
