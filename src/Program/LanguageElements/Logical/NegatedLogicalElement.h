#ifndef TKOM_NEGATEDLOGICALELEMENT_H
#define TKOM_NEGATEDLOGICALELEMENT_H


#include "../Variables/Assignable.h"
#include <memory>

class NegatedLogicalElement: public Assignable {
    std::unique_ptr<Assignable> element;
public:
    explicit NegatedLogicalElement(std::unique_ptr<Assignable> element_): element{ std::move(element_) }, Assignable() {}

    void be_evaluated(Evaluator *interpreter) override;

    const std::unique_ptr<Assignable> & getElement() const;
};


#endif //TKOM_NEGATEDLOGICALELEMENT_H
