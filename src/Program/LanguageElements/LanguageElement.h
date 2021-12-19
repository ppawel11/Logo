#ifndef TKOM_LANGUAGEELEMENT_H
#define TKOM_LANGUAGEELEMENT_H

class Interpreter;

class LanguageElement {
public:
    LanguageElement() { } ;
    LanguageElement(const LanguageElement&) = delete;
    LanguageElement(LanguageElement&&) = default;

    virtual void be_handled(Interpreter *interpreter) {};
};


#endif //TKOM_LANGUAGEELEMENT_H
