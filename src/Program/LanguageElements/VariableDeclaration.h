#ifndef TKOM_VARIABLEDECLARATION_H
#define TKOM_VARIABLEDECLARATION_H

#include "LanguageElement.h"

class VariableDeclaration: public LanguageElement {
public:
    void be_handled(Parser *parser) override;
};


#endif //TKOM_VARIABLEDECLARATION_H
