#ifndef TKOM_VARIABLEDECLARATION_H
#define TKOM_VARIABLEDECLARATION_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include <string>
#include <utility>

class VariableDeclaration: public LanguageElement {
    std::string label;
    Assignable value;
public:
    VariableDeclaration(std::string label_, Assignable value_):
        label {std::move( label_ )},
        value { value_ },
        LanguageElement()
    {
    }

    void be_handled(Interpreter *interpreter) override {

    }
};


#endif //TKOM_VARIABLEDECLARATION_H
