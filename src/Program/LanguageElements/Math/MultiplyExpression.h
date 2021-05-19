#ifndef TKOM_MULTIPLYEXPRESSION_H
#define TKOM_MULTIPLYEXPRESSION_H


#include "MathElement.h"
#include "MultiplyOperator.h"
#include <utility>
#include <vector>


class MultiplyExpression {
    std::vector<MathElement> elements;
    std::vector<MultiplyOperator> operators;

public:
    MultiplyExpression( std::vector<MathElement> elements_, std::vector<MultiplyOperator> operators_ ):
        elements{ std::move(elements_) },
        operators{ std::move(operators_) }
    {}
};


#endif //TKOM_MULTIPLYEXPRESSION_H
