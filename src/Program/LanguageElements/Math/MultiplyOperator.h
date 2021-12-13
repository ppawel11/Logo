#ifndef TKOM_MULTIPLYOPERATOR_H


#define TKOM_MULTIPLYOPERATOR_H

#include "OperationType.h"
#include <stdexcept>

class MultiplyOperator {
    OperationType type;
public:
    explicit MultiplyOperator(OperationType type_) {
        if( type != OperationType::MULTIPLY && type != OperationType::DIVIDE )
        {
            throw std::runtime_error("multiply operator invalid");
        }
        type = type_;
    }

    OperationType getType() const;
};


#endif //TKOM_MULTIPLYOPERATOR_H
