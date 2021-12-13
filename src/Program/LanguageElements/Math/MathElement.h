#ifndef TKOM_MATHELEMENT_H
#define TKOM_MATHELEMENT_H

#include <optional>
#include <memory>
#include "../FunctionCall.h"

class AdditiveExpression;

class MathElement: public Assignable {
    // [“-”], ( label | number | function_call | parentheses_expression )
    bool is_negated;

    std::optional<int> int_value;
    std::optional<std::string> label;
    std::optional<Assignable*> func_call;
    Assignable* parent_expression;

public:
    MathElement(int value_, bool is_negated_):
        int_value { value_ },
        is_negated { is_negated_ },
        Assignable()
    {}

    MathElement(std::string label_, bool is_negated_):
        label { label_ },
        is_negated { is_negated_ },
        Assignable()
    {}

    MathElement(Assignable * value, bool is_negated_, bool is_parented = false):
        is_negated { is_negated_ },
        Assignable()
    {
        if( is_parented )
        {
            parent_expression = value;
        }
        else
        {
            func_call = value;
        }
    }

    void be_evaluated(Interpreter *interpreter) override;

};

#endif //TKOM_MATHELEMENT_H
