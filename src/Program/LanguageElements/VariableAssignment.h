#ifndef TKOM_VARIABLEASSIGNMENT_H
#define TKOM_VARIABLEASSIGNMENT_H

#include <string>
#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "../Program.h"
#include <iostream>

class VariableAssignment: public LanguageElement {
    std::string label;
    Assignable * value;

public:
    VariableAssignment(const std::string &label_, Assignable * value_) :
        label {label_ },
        value {value_ },
        LanguageElement()
    {}

    void be_handled(Interpreter *interpreter) override;

    const std::string &getLabel() const;

    Assignable *getValue() const;
};


#endif //TKOM_VARIABLEASSIGNMENT_H
