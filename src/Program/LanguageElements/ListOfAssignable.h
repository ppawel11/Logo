#ifndef TKOM_LISTOFASSIGNABLE_H
#define TKOM_LISTOFASSIGNABLE_H

#include "Variables/Assignable.h"
#include <utility>
#include <vector>
#include <memory>

class ListOfAssignable: public Assignable {
    std::vector<std::unique_ptr<Assignable>> elements;

public:
    explicit ListOfAssignable(std::vector<std::unique_ptr<Assignable>> elements_): elements{std::move( elements_ )}, Assignable() {}

    void be_evaluated(Evaluator *interpreter) override;

    const std::vector<std::unique_ptr<Assignable>> & get_elements();
};


#endif //TKOM_LISTOFASSIGNABLE_H
