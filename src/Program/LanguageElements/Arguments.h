#ifndef TKOM_ARGUMENTS_H
#define TKOM_ARGUMENTS_H


#include "Variables/Assignable.h"
#include <utility>
#include <vector>
#include <memory>

class Arguments {
    std::vector<std::unique_ptr<Assignable>> args;

public:
    Arguments():
        args {}
    {}

    explicit Arguments(std::vector <std::unique_ptr<Assignable>> args_):
        args{std::move( args_ )}
    {}

    const std::vector<std::unique_ptr<Assignable>> & getArgs() const {
        return args;
    }

};


#endif //TKOM_ARGUMENTS_H
