#ifndef TKOM_VARIABLEDECLARATION_H
#define TKOM_VARIABLEDECLARATION_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include <string>
#include <utility>
#include <memory>

class VariableDeclaration: public LanguageElement {
    std::string label;
    std::unique_ptr<Assignable> value;
public:
    VariableDeclaration(std::string label_, std::unique_ptr<Assignable> value_):
        label {std::move( label_ )},
        value { std::move(value_) },
        LanguageElement()
    {
    }

    void be_handled(Interpreter *interpreter) override;

    const std::string &getLabel() const;

    const std::unique_ptr<Assignable> & getValue() const;
};


#endif //TKOM_VARIABLEDECLARATION_H
