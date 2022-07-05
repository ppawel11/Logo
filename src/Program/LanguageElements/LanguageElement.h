#ifndef TKOM_LANGUAGEELEMENT_H
#define TKOM_LANGUAGEELEMENT_H

#include "LanguageElementVisitor.h"

class LanguageElementVisitor;

class LanguageElement {
public:
//    LanguageElement() { } ;
//    LanguageElement(const LanguageElement&) = delete;
//    LanguageElement(LanguageElement&&) = default;

    virtual void be_handled(LanguageElementVisitor *interpreter) {};
};


#endif //TKOM_LANGUAGEELEMENT_H
