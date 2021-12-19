#ifndef TKOM_LISTOFASSIGNABLE_H
#define TKOM_LISTOFASSIGNABLE_H

#include "Variables/Assignable.h"
#include <utility>
#include <vector>

class ListOfAssignable: public Assignable {
    std::vector<Assignable*> elements;

public:
    ListOfAssignable(std::vector<Assignable*> elements_): elements{std::move( elements_ )}, Assignable() {}

    void be_evaluated(Interpreter *interpreter) override;

    std::vector<Assignable*> get_elements();
};


#endif //TKOM_LISTOFASSIGNABLE_H
