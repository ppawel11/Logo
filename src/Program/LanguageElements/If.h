#ifndef TKOM_IF_H
#define TKOM_IF_H

#include <utility>

#include "../Statement.h"
#include "Block.h"
#include "Logical/OrCondition.h"

class If: public LanguageElement {
    Block if_block;
    std::optional<Block> else_block;
    OrCondition condition;

public:
    If(OrCondition condition_, Block if_block_, std::optional<Block> else_block_):
        condition{std::move( condition_ )},
        if_block{std::move( if_block_ )},
        else_block{std::move( else_block_ )}
    {}

    void be_handled(Parser *parser) override {

    }
};


#endif //TKOM_IF_H
