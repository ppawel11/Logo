#ifndef TKOM_RETURN_H
#define TKOM_RETURN_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "../Program.h"

class Return: public LanguageElement {
    Assignable * value;
public:
    explicit Return( Assignable * value_ ): value{ value_ }, LanguageElement() {}

    void be_handled(Interpreter *interpreter) override;

    Assignable *getValue() const;
};


#endif //TKOM_RETURN_H
