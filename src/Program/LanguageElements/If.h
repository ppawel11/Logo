#ifndef TKOM_IF_H
#define TKOM_IF_H

#include <utility>

#include "Block.h"
#include "Logical/OrCondition.h"
#include "../Program.h"

class If: public LanguageElement {
    LanguageElement * if_block;
    std::optional<LanguageElement *> else_block;
    Assignable* condition;

public:
    If(Assignable* condition_, LanguageElement* if_block_, std::optional<LanguageElement*> else_block_):
        condition{ condition_ },
        if_block{ if_block_ },
        else_block{ else_block_ }
    {}

    void be_handled(Interpreter *interpreter) override;

    LanguageElement *getIfBlock() const;

    const std::optional<LanguageElement *> &getElseBlock() const;

    Assignable *getCondition() const;
};


#endif //TKOM_IF_H
