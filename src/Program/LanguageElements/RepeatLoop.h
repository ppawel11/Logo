#ifndef TKOM_REPEATLOOP_H
#define TKOM_REPEATLOOP_H

#include "LanguageElement.h"
#include "Math/AdditiveExpression.h"
#include "Block.h"
#include <utility>
#include <vector>

class RepeatLoop: public LanguageElement {
    AdditiveExpression repeats;
    Block loop;

public:
    RepeatLoop(AdditiveExpression repeats_, Block loop_ ):
        repeats{ repeats_ },
        loop{ loop_ },
        LanguageElement()
    {}

    void be_handled(Parser *parser) override {

    }
};


#endif //TKOM_REPEATLOOP_H
