#ifndef TKOM_READ_H
#define TKOM_READ_H

#include "../../Program/LanguageElements/LanguageElement.h"


class Read: public LanguageElement {
public:
    Read() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_READ_H
