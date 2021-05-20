#ifndef TKOM_ORCONDITION_H
#define TKOM_ORCONDITION_H

#include <vector>
#include "AndCondition.h"
#include "../Variables/Assignable.h"

class OrCondition: public Assignable {
    std::vector<AndCondition> elements;

public:
    explicit OrCondition( std::vector<AndCondition> elements_):
        elements{ std::move(elements_) },
        Assignable()
    {}
};


#endif //TKOM_ORCONDITION_H
