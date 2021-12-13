#ifndef TKOM_LIST_H
#define TKOM_LIST_H

#include "Assignable.h"

class List: public Assignable {
    std::vector<Assignable*> elements;

public:
    List(const std::vector<Assignable*> &elements) : elements{ elements } {}

    void be_evaluated(Interpreter *interpreter) override;

    const std::vector<Assignable *> &get_elements() const;
};


#endif //TKOM_LIST_H
