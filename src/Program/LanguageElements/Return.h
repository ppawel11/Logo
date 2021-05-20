#ifndef TKOM_RETURN_H
#define TKOM_RETURN_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "../Program.h"

class Return: public LanguageElement {
    Assignable content;
public:
    explicit Return( Assignable content_ ): content{ content_ }, LanguageElement() {}

    void be_handled(Interpreter *interpreter) override {

    }
};


#endif //TKOM_RETURN_H
