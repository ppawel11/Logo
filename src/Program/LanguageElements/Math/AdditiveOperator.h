#ifndef TKOM_ADDITIVEOPERATOR_H
#define TKOM_ADDITIVEOPERATOR_H

#include "OperationType.h"
#include <stdexcept>

class AdditiveOperator {
    OperationType type;
public:
    explicit AdditiveOperator(OperationType type_) {
        if( type_ != OperationType::SUBSTRACTION && type_ != OperationType::SUM )
        {
            throw std::runtime_error("additive operator invalid");
        }
        type = type_;
    }

    OperationType getType() const {
        return type;
    }
};

#endif //TKOM_ADDITIVEOPERATOR_H
