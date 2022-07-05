#ifndef TKOM_CLEAR_H
#define TKOM_CLEAR_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Clear: public LanguageElement {
public:
    Clear() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_CLEAR_H
