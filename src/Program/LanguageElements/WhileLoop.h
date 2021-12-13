#ifndef TKOM_WHILELOOP_H
#define TKOM_WHILELOOP_H

#include "LanguageElement.h"
#include "Block.h"
#include "Logical/OrCondition.h"
#include <utility>
#include <vector>

class WhileLoop: public LanguageElement {
    Assignable * condition;
    LanguageElement* loop;

public:
    WhileLoop(Assignable * condition_, LanguageElement* loop_ ):
        condition{ condition_ }, loop{ loop_ }, LanguageElement() {}

    void be_handled(Interpreter *interpreter) override;

    Assignable *getCondition() const;

    LanguageElement *getLoop() const;
};


#endif //TKOM_WHILELOOP_H
