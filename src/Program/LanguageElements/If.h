#ifndef TKOM_IF_H
#define TKOM_IF_H

#include <utility>

#include "Block.h"
#include "Logical/OrCondition.h"
#include "../Program.h"

class If: public LanguageElement {
    std::unique_ptr<LanguageElement> if_block;
    std::optional<std::unique_ptr<LanguageElement>> else_block;
    std::unique_ptr<Assignable> condition;

public:
    If(std::unique_ptr<Assignable> condition_, std::unique_ptr<LanguageElement> if_block_, std::optional<std::unique_ptr<LanguageElement>> else_block_):
        condition{ std::move(condition_) },
        if_block{ std::move(if_block_) },
        else_block{ std::move(else_block_) }
    {}

    void be_handled(LanguageElementVisitor *interpreter) override;

    const std::unique_ptr<LanguageElement> & getIfBlock() const;

    const std::optional<std::unique_ptr<LanguageElement>> & getElseBlock() const;

    const std::unique_ptr<Assignable> & getCondition() const;
};


#endif //TKOM_IF_H
