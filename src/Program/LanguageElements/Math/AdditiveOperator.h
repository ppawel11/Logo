#ifndef TKOM_ADDITIVEOPERATOR_H
#define TKOM_ADDITIVEOPERATOR_H

#include "OperationType.h"
#include <stdexcept>

class AdditiveOperator {
    OperationType type;
public:
    explicit AdditiveOperator(OperationType type_) {
        if( type != OperationType::SUBSTRACTION && type != OperationType::SUM )
        {
            throw std::runtime_error("additive operator invalid");
        }
        type = type_;
    }
};

#endif //TKOM_ADDITIVEOPERATOR_H
