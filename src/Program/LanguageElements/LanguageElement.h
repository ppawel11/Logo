#ifndef TKOM_LANGUAGEELEMENT_H
#define TKOM_LANGUAGEELEMENT_H

class Parser;

class LanguageElement {
public:
    virtual void be_handled(Parser* parser) = 0;
};


#endif //TKOM_LANGUAGEELEMENT_H
