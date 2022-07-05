#ifndef TKOM_WRITE_H
#define TKOM_WRITE_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Write: public LanguageElement {
public:
    Write() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_WRITE_H
