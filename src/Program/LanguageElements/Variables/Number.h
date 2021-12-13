#ifndef TKOM_NUMBER_H
#define TKOM_NUMBER_H


#include "Assignable.h"

class Number: public Assignable {
    int value;
public:
    explicit Number(int value_): value{value_}, Assignable() {}

    void be_evaluated(Interpreter *interpreter) override;

    int get_value() const;

};


#endif //TKOM_NUMBER_H
