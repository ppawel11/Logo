#ifndef TKOM_NUMBER_H
#define TKOM_NUMBER_H


#include "Assignable.h"
#include "VariantValue.h"

class Number: public Assignable {
    int value;

public:
    int getValue() const;

    void setValue(int value);

    Number(): value{0} {};
    explicit Number(int value_): value{value_}, Assignable() {}
    ~Number() = default;
    void be_evaluated(Evaluator *interpreter) override;

};


#endif //TKOM_NUMBER_H
