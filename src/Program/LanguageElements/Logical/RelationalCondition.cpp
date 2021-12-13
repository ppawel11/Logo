#include "RelationalCondition.h"
#include "OrCondition.h"
#include "../../../Interpreter/Interpreter.h"

RelationalCondition::RelationalCondition(bool is_negated_, bool literal_value_):
        is_negated{ is_negated_ },
        literal_value{ literal_value_ }
{}

RelationalCondition::RelationalCondition(bool is_negated_, Assignable *value, bool is_parented):
    is_negated{ is_negated_ },
    Assignable()
{
    if( is_parented )
    {
        parent_condition = value;
    }
    else
    {
        comparison = value;
    }
}

void RelationalCondition::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}
