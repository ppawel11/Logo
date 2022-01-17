#ifndef TKOM_SWITCH_H
#define TKOM_SWITCH_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Switch: public LanguageElement {
public:
    Switch() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_SWITCH_H
