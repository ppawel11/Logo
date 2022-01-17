#ifndef TKOM_TURN_H
#define TKOM_TURN_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Turn: public LanguageElement {
public:
    Turn() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_TURN_H
