#ifndef TKOM_VARIABLEASSIGNMENT_H
#define TKOM_VARIABLEASSIGNMENT_H

#include <string>
#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "../Program.h"
#include <iostream>
#include <utility>

class VariableAssignment: public LanguageElement {
    std::string label;
    std::unique_ptr<Assignable> value;

public:
    VariableAssignment(std::string label_, std::unique_ptr<Assignable> value_) :
        label {std::move(label_ )},
        value { std::move(value_) },
        LanguageElement()
    {}

    void be_handled(Interpreter *interpreter) override;

    const std::string &getLabel() const;

    const std::unique_ptr<Assignable> & getValue() const;
};


#endif //TKOM_VARIABLEASSIGNMENT_H
