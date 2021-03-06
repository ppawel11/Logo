#ifndef TKOM_FUNCTIONCALL_H
#define TKOM_FUNCTIONCALL_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "Arguments.h"
#include "../Program.h"
#include <string>
#include <utility>
#include <vector>

class FunctionCall: public LanguageElement, public Assignable {
    std::string name;
    Arguments arguments;
public:
    const std::string &getName() const;

    const Arguments &getArguments() const;

public:
    FunctionCall(std::string name_, Arguments arguments_):
        name{std::move( name_ )}, arguments{std::move( arguments_ )}, LanguageElement() {}
//
    void be_handled(LanguageElementVisitor *interpreter) override;
//    explicit FunctionCall(std::string name_):
//        name{std::move( name_ )}, arguments(), Statement() {}
    void be_evaluated(Evaluator *interpreter) override;
};


#endif //TKOM_FUNCTIONCALL_H
