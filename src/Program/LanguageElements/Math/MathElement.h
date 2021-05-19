#ifndef TKOM_MATHELEMENT_H
#define TKOM_MATHELEMENT_H

#include <optional>
#include <memory>
#include "../FunctionCall.h"

class AdditiveExpression;

class MathElement {
    bool is_negated;

    std::optional<int> value;
    std::optional<std::string> label;
    std::optional<FunctionCall> func_call;
    AdditiveExpression* parent_expression;

public:
    MathElement(int value_, bool is_negated_):
        value { value_ },
        is_negated { is_negated_ }
    {}

    MathElement(std::string label_, bool is_negated_):
        label { label_ },
        is_negated { is_negated_ }
    {}

    MathElement(FunctionCall func_call_, bool is_negated_):
        func_call { func_call_ },
        is_negated { is_negated_ }
    {}

    MathElement(AdditiveExpression* parent_expression_, bool is_negated_);
};


#endif //TKOM_MATHELEMENT_H
