#ifndef TKOM_VARIABLEASSIGNMENT_H
#define TKOM_VARIABLEASSIGNMENT_H

#include <string>
#include "LanguageElement.h"
#include "Variables/Assignable.h"

class VariableAssignment: public LanguageElement {
    std::string label;
    Assignable value;

public:
    VariableAssignment(const std::string &label_, const Assignable &value_) :
        label {label_ },
        value {value_ },
        LanguageElement()
    {}

    void be_handled(Parser *parser) override {

    }
};


#endif //TKOM_VARIABLEASSIGNMENT_H
