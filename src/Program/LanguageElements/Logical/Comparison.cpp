#include "Comparison.h"
#include "../../../Interpreter/Interpreter.h"

void Comparison::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

const std::unique_ptr<Assignable> & Comparison::getFirstExpression() const {
    return first_expression;
}

const std::optional<std::unique_ptr<Assignable>> & Comparison::getSecondExpression() const {
    return second_expression;
}

const std::optional<RelationType> &Comparison::getType() const {
    return type;
}
