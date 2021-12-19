#ifndef TKOM_COMPARISON_H
#define TKOM_COMPARISON_H


#include <optional>
#include "../Math/AdditiveExpression.h"
#include "RelationType.h"

class Comparison: public Assignable {
    // additive_expression, [ comparison_operator, additive_expression ]
    Assignable* first_expression;
    std::optional<Assignable*> second_expression;
    std::optional<RelationType> type;

public:
    explicit Comparison( Assignable* first_expression_ ) :
            first_expression{ first_expression_ },
            type{ std::nullopt },
            second_expression{ std::nullopt }
    {}

    Comparison(
            Assignable* first_expression_,
            RelationType type_,
            Assignable* second_expression_
    ) :
        first_expression{ first_expression_ },
        type{ type_ },
        second_expression{ second_expression_ }
    {}

    void be_evaluated(Interpreter *interpreter) override;

    Assignable *getFirstExpression() const;

    const std::optional<Assignable *> &getSecondExpression() const;

    const std::optional<RelationType> &getType() const;
};


#endif //TKOM_COMPARISON_H
