#ifndef TKOM_NEGATEDMATHELEMENT_H
#define TKOM_NEGATEDMATHELEMENT_H


#include "../Variables/Assignable.h"

class NegatedMathElement: public Assignable {
    Assignable* element;
public:
    explicit NegatedMathElement(Assignable* element_): element{element_}, Assignable() {}

    void be_evaluated(Interpreter *interpreter) override;

    Assignable *getElement() const;
};


#endif //TKOM_NEGATEDMATHELEMENT_H
