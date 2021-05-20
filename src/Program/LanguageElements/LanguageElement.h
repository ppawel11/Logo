#ifndef TKOM_LANGUAGEELEMENT_H
#define TKOM_LANGUAGEELEMENT_H

class Interpreter;

class LanguageElement {
public:
    virtual void be_handled(Interpreter *interpreter) = 0;
};


#endif //TKOM_LANGUAGEELEMENT_H
