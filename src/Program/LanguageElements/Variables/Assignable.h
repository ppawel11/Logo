#ifndef TKOM_ASSIGNABLE_H
#define TKOM_ASSIGNABLE_H

#include <variant>

class Interpreter;

class Assignable {
public:
    virtual void be_evaluated(Interpreter * interpreter) = 0;
};


#endif //TKOM_ASSIGNABLE_H
