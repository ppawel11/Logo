#ifndef TKOM_WHILELOOP_H
#define TKOM_WHILELOOP_H

#include "LanguageElement.h"
#include "Block.h"
#include "Logical/OrCondition.h"
#include <utility>
#include <vector>

class WhileLoop: public LanguageElement {
    OrCondition condition;
    Block loop;

public:
    WhileLoop(OrCondition condition_, Block loop_ ):
        condition{std::move( condition_ )}, loop{std::move(loop_)}, LanguageElement() {}

    void be_handled(Parser *parser) override {

    }
};


#endif //TKOM_WHILELOOP_H
