#ifndef TKOM_EQUALITYCONDITION_H
#define TKOM_EQUALITYCONDITION_H

#include <utility>
#include "RelationalCondition.h"
#include <optional>

class EqualityCondition {
    RelationalCondition first_condition;
    std::optional<RelationalCondition> second_condition;
    std::optional<bool> equals;
public:
    explicit EqualityCondition( RelationalCondition first_condition_ ) :
        first_condition{ std::move(first_condition_) }
    {}

    EqualityCondition( RelationalCondition first_condition_, bool equals_, RelationalCondition second_condition_ ) :
        first_condition{ std::move(first_condition_) },
        equals{ equals_ },
        second_condition{ std::move(second_condition_) }
    {}
};


#endif //TKOM_EQUALITYCONDITION_H
