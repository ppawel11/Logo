#ifndef TKOM_RELATIONALCONDITION_H
#define TKOM_RELATIONALCONDITION_H

#include <optional>
#include "RelationType.h"
#include "Comparison.h"

class OrCondition;

class RelationalCondition {
    bool is_negated;

    std::optional<Comparison> comparison;

    std::optional<bool> literal_value;

    OrCondition* parent_condition;

public:
    RelationalCondition( bool is_negated_, Comparison comparison_ );

    RelationalCondition( bool is_negated_, bool literal_value_ );

    RelationalCondition(bool is_negated_, OrCondition *parent_ );
};


#endif //TKOM_RELATIONALCONDITION_H
