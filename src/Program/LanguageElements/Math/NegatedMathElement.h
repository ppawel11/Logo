#ifndef TKOM_NEGATEDMATHELEMENT_H
#define TKOM_NEGATEDMATHELEMENT_H


#include "../Variables/Assignable.h"
#include <memory>

class NegatedMathElement: public Assignable {
    std::unique_ptr<Assignable> element;
public:
    explicit NegatedMathElement(std::unique_ptr<Assignable> element_): element{ std::move(element_) }, Assignable() {}

    void be_evaluated(Evaluator *interpreter) override;

    const std::unique_ptr<Assignable> & getElement() const;
};


#endif //TKOM_NEGATEDMATHELEMENT_H
