#ifndef TKOM_COMPARISON_H
#define TKOM_COMPARISON_H


#include "../Math/AdditiveExpression.h"
#include "RelationType.h"

class Comparison {
    AdditiveExpression first_expression;
    std::optional<AdditiveExpression> second_expression;
    std::optional<RelationType> type;

public:
    explicit Comparison( AdditiveExpression first_expression_ ) :
            first_expression{ std::move(first_expression_) },
            type{ std::nullopt },
            second_expression{ std::nullopt }
    {}

    Comparison(
            AdditiveExpression first_expression_,
            RelationType type_,
            AdditiveExpression second_expression_
    ) :
        first_expression{ std::move(first_expression_) },
        type{ type_ },
        second_expression{ std::move(second_expression_) }
    {}
};


#endif //TKOM_COMPARISON_H
