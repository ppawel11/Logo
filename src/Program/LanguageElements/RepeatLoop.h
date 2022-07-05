#ifndef TKOM_REPEATLOOP_H
#define TKOM_REPEATLOOP_H

#include "LanguageElement.h"
#include "Math/AdditiveExpression.h"
#include "Block.h"
#include <utility>
#include <vector>
#include <iostream>

class RepeatLoop: public LanguageElement {
    std::unique_ptr<Assignable> repeats;
    std::unique_ptr<LanguageElement> loop;

public:
    RepeatLoop(std::unique_ptr<Assignable> repeats_, std::unique_ptr<LanguageElement> loop_ ):
        repeats{ std::move(repeats_) },
        loop{ std::move(loop_) },
        LanguageElement()
    {}

    void be_handled(LanguageElementVisitor *interpreter) override;

    const std::unique_ptr<Assignable> & getRepeats() const;

    const std::unique_ptr<LanguageElement> & getLoop() const;
};


#endif //TKOM_REPEATLOOP_H
