#ifndef TKOM_ARGUMENTS_H
#define TKOM_ARGUMENTS_H


#include "Variables/Assignable.h"
#include <utility>
#include <vector>

class Arguments {
    std::vector<Assignable> args;

public:
    Arguments():
        args {}
    {}

    explicit Arguments(std::vector <Assignable> args_):
        args{std::move(args_)}
    {}

};


#endif //TKOM_ARGUMENTS_H
