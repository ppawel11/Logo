#ifndef TKOM_ADDITIVEEXPRESSION_H
#define TKOM_ADDITIVEEXPRESSION_H

#include <utility>

#include "../Variables/Assignable.h"
#include "OperationType.h"
#include "MultiplyExpression.h"
#include "AdditiveOperator.h"


class AdditiveExpression: public Assignable {
    // multiply_expression, { additive_operator, multiply_expression }
    std::vector<Assignable*> expressions;
    std::vector<AdditiveOperator> operators; // true - add, false - sub

public:
    AdditiveExpression() {}

    AdditiveExpression(std::vector<Assignable*> expressions_, std::vector<AdditiveOperator> operators_ ):
        expressions{ std::move(expressions_) },
        operators{ std::move(operators_) }
    {}

    void be_evaluated(Interpreter *interpreter) override;

    const std::vector<Assignable *> &getExpressions() const;

    const std::vector<AdditiveOperator> &getOperators() const;
};


#endif //TKOM_ADDITIVEEXPRESSION_H
