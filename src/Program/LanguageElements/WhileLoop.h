#ifndef TKOM_WHILELOOP_H
#define TKOM_WHILELOOP_H

#include "LanguageElement.h"
#include "Block.h"
#include "Logical/OrCondition.h"
#include <utility>
#include <vector>

class WhileLoop: public LanguageElement {
    std::unique_ptr<Assignable> condition;
    std::unique_ptr<LanguageElement> loop;

public:
    WhileLoop(std::unique_ptr<Assignable> condition_, std::unique_ptr<LanguageElement> loop_ ):
        condition{ std::move(condition_) }, loop{ std::move(loop_) }, LanguageElement() {}

    void be_handled(LanguageElementVisitor *interpreter) override;

    const std::unique_ptr<Assignable> & getCondition() const;

    const std::unique_ptr<LanguageElement> & getLoop() const;
};


#endif //TKOM_WHILELOOP_H
