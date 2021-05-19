#include "RelationalCondition.h"
#include "OrCondition.h"

RelationalCondition::RelationalCondition(bool is_negated_, OrCondition *parent_):
        is_negated{ is_negated_ },
        parent_condition{ parent_ }
{
}

RelationalCondition::RelationalCondition(bool is_negated_, Comparison comparison_):
        is_negated{ is_negated_ },
        comparison{ comparison_ },
        parent_condition{ nullptr }
{}

RelationalCondition::RelationalCondition(bool is_negated_, bool literal_value_):
        is_negated{ is_negated_ },
        literal_value{ literal_value_ },
        parent_condition{ nullptr }
{}
