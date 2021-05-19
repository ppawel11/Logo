#ifndef TKOM_LIST_H
#define TKOM_LIST_H

#include "Assignable.h"

class List: public Assignable {
    std::vector<Assignable> elements;

public:
    List(const std::vector<Assignable> &elements) : elements{ elements } {}
};


#endif //TKOM_LIST_H
