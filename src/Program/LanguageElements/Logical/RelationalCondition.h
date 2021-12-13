#ifndef TKOM_RELATIONALCONDITION_H
#define TKOM_RELATIONALCONDITION_H

#include <optional>
#include "RelationType.h"
#include "Comparison.h"

class OrCondition;

class RelationalCondition: public Assignable {
    // [“!”] ( comparison | “true” | “false” | parentheses_condition )
    bool is_negated;

    std::optional<bool> literal_value;

    std::optional<Assignable*> comparison;

    std::optional<Assignable*> parent_condition;

public:
    RelationalCondition( bool is_negated_, Assignable *comparison_, bool is_parented = false );

    RelationalCondition( bool is_negated_, bool literal_value_ );

    void be_evaluated(Interpreter *interpreter) override;
};


#endif //TKOM_RELATIONALCONDITION_H
