#ifndef TKOM_REPEATLOOP_H
#define TKOM_REPEATLOOP_H

#include "LanguageElement.h"
#include "Math/AdditiveExpression.h"
#include "Block.h"
#include <utility>
#include <vector>
#include <iostream>

class RepeatLoop: public LanguageElement {
    Assignable * repeats;
    LanguageElement* loop;

public:
    RepeatLoop(Assignable * repeats_, LanguageElement * loop_ ):
        repeats{ repeats_ },
        loop{ loop_ },
        LanguageElement()
    {}

    void be_handled(Interpreter *interpreter) override;

    Assignable *getRepeats() const;

    LanguageElement *getLoop() const;
};


#endif //TKOM_REPEATLOOP_H
