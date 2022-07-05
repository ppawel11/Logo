#ifndef TKOM_COMPARISON_H
#define TKOM_COMPARISON_H


#include <optional>
#include "../Math/AdditiveExpression.h"
#include "RelationType.h"

class Comparison: public Assignable {
    // additive_expression, [ comparison_operator, additive_expression ]
    std::unique_ptr<Assignable> first_expression;
    std::optional<std::unique_ptr<Assignable>> second_expression;
    std::optional<RelationType> type;

public:
    explicit Comparison( std::unique_ptr<Assignable> first_expression_ ) :
            first_expression{ std::move(first_expression_) },
            type{ std::nullopt },
            second_expression{ std::nullopt }
    {}

    Comparison(
            std::unique_ptr<Assignable> first_expression_,
            RelationType type_,
            std::unique_ptr<Assignable> second_expression_
    ) :
        first_expression{ std::move(first_expression_) },
        type{ type_ },
        second_expression{ std::move(second_expression_) }
    {}

    void be_evaluated(Evaluator *interpreter) override;

    const std::unique_ptr<Assignable> & getFirstExpression() const;

    const std::optional<std::unique_ptr<Assignable>> & getSecondExpression() const;

    const std::optional<RelationType> &getType() const;
};


#endif //TKOM_COMPARISON_H
