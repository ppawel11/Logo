#ifndef TKOM_FORWARD_H
#define TKOM_FORWARD_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Forward: public LanguageElement {
public:
    Forward() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_FORWARD_H
