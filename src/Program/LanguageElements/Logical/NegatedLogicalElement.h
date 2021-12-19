#ifndef TKOM_NEGATEDLOGICALELEMENT_H
#define TKOM_NEGATEDLOGICALELEMENT_H


#include "../Variables/Assignable.h"

class NegatedLogicalElement: public Assignable {
    Assignable * element;
public:
    explicit NegatedLogicalElement(Assignable* element_): element{ element_} {}

    void be_evaluated(Interpreter *interpreter) override;

    Assignable *getElement() const;
};


#endif //TKOM_NEGATEDLOGICALELEMENT_H
