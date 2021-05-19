#ifndef TKOM_STRING_H
#define TKOM_STRING_H

#include "Assignable.h"
#include <string>
#include <utility>
class String: public Assignable {
    std::string value;
public:
    explicit String( std::string value_ ): value{std::move(value_)}, Assignable() {}
};


#endif //TKOM_STRING_H
