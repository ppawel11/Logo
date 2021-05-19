#ifndef TKOM_RETURN_H
#define TKOM_RETURN_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"

class Return: public LanguageElement {
    Assignable content;
public:
    explicit Return( Assignable content_ ): content{ content_ }, LanguageElement() {}

    void be_handled(Parser *parser) override {

    }
};


#endif //TKOM_RETURN_H
