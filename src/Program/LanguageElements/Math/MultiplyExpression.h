#ifndef TKOM_MULTIPLYEXPRESSION_H
#define TKOM_MULTIPLYEXPRESSION_H


#include "../Variables/Assignable.h"
#include "MultiplyOperator.h"
#include <utility>
#include <vector>
#include <memory>

class MultiplyExpression: public Assignable {
    // math_element, { multiply_operator, math_element }
    std::vector<std::unique_ptr<Assignable>> elements;
    std::vector<MultiplyOperator> operators;

public:
    MultiplyExpression( std::vector<std::unique_ptr<Assignable>> elements_, std::vector<MultiplyOperator> operators_ ):
        elements{ std::move(elements_) },
        operators{ std::move(operators_) },
        Assignable()
    {}

    void be_evaluated(Interpreter *interpreter) override;

    const std::vector<std::unique_ptr<Assignable>> & getElements() const;

    const std::vector<MultiplyOperator> &getOperators() const;
};


#endif //TKOM_MULTIPLYEXPRESSION_H
