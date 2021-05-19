#ifndef TKOM_ORCONDITION_H
#define TKOM_ORCONDITION_H

#include <vector>
#include "AndCondition.h"

class OrCondition {
    std::vector<AndCondition> elements;

public:
    explicit OrCondition( std::vector<AndCondition> elements_):
        elements{ std::move(elements_) }
    {}
};


#endif //TKOM_ORCONDITION_H
