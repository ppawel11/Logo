#include "MathElement.h"
#include "AdditiveExpression.h"

MathElement::MathElement(AdditiveExpression* parent_expression_, bool is_negated_):
        parent_expression { std::move(parent_expression_) },
        is_negated { is_negated_ }
{}
