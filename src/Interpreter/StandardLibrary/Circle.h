#ifndef TKOM_CIRCLE_H
#define TKOM_CIRCLE_H

#include "../../Program/LanguageElements/LanguageElement.h"

class Circle: public LanguageElement {
public:
    Circle() = default;

    void be_handled(LanguageElementVisitor *interpreter) override;
};

#endif //TKOM_CIRCLE_H
