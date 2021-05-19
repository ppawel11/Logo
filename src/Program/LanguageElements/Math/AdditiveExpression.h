#ifndef TKOM_ADDITIVEEXPRESSION_H
#define TKOM_ADDITIVEEXPRESSION_H

#include <utility>

#include "../Variables/Assignable.h"
#include "OperationType.h"
#include "MultiplyExpression.h"
#include "AdditiveOperator.h"


class AdditiveExpression: public Assignable {
    std::vector<MultiplyExpression> expressions;
    std::vector<AdditiveOperator> operators; // true - add, false - sub

public:
    AdditiveExpression() {}

    AdditiveExpression(std::vector<MultiplyExpression> expressions_, std::vector<AdditiveOperator> operators_ ):
        expressions{ std::move(expressions_) },
        operators{ std::move(operators_) }
    {}
};


#endif //TKOM_ADDITIVEEXPRESSION_H
