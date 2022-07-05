#ifndef TKOM_RESET_H
#define TKOM_RESET_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Reset: public LanguageElement {
public:
    Reset() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_RESET_H
