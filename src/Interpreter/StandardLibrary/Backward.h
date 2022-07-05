#ifndef TKOM_BACKWARD_H
#define TKOM_BACKWARD_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Backward: public LanguageElement {
public:
    Backward() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_BACKWARD_H


