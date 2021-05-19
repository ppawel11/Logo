#ifndef TKOM_LOGICALELEMENT_H
#define TKOM_LOGICALELEMENT_H


#include <optional>
#include <utility>
#include "../Math/AdditiveExpression.h"

class Condition;

class LogicalElement {
    bool is_negated;

    std::optional<AdditiveExpression> expression;
    std::optional<bool> direct_value;
    Condition* parent_condition;
public:
    LogicalElement(bool is_negated_, std::optional<AdditiveExpression> expression_) :
        is_negated{ is_negated_ },
        expression{std::move( expression_ )}
    {}

    LogicalElement(bool is_negated_, Condition *parent_condition_) :
        is_negated{ is_negated_ },
        parent_condition{ parent_condition_ }
    {}

    LogicalElement(bool is_negated_, bool direct_value_ ) :
        is_negated{ is_negated_ },
        direct_value{ direct_value_ }
    {}

};


#endif //TKOM_LOGICALELEMENT_H
