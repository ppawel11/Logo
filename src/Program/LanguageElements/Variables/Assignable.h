#ifndef TKOM_ASSIGNABLE_H
#define TKOM_ASSIGNABLE_H

#include <variant>

class Interpreter;

class Assignable {
public:
    Assignable() = default ;
//    Assignable(const Assignable&) = delete;
//    Assignable(Assignable&&) = default;

    virtual void be_evaluated(Interpreter * interpreter) = 0;
};


#endif //TKOM_ASSIGNABLE_H
