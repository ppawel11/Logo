#ifndef TKOM_FOREACHLOOP_H
#define TKOM_FOREACHLOOP_H

#include <string>
#include <utility>
#include <vector>
#include "LanguageElement.h"
#include "Block.h"
#include "../Program.h"

class ForEachLoop: public LanguageElement {
    std::string value_label;
    std::unique_ptr<Assignable> container;
    std::unique_ptr<LanguageElement> loop;

public:
    ForEachLoop(std::string value_label_, std::unique_ptr<Assignable> container_label_, std::unique_ptr<LanguageElement> loop_):
            value_label{std::move( value_label_ )},
            container{std::move(container_label_ )},
            loop{ std::move(loop_) } {}

    void be_handled(Interpreter *interpreter) override;

    const std::string &getValueLabel() const;

    const std::unique_ptr<Assignable> & getContainer() const;

    const std::unique_ptr<LanguageElement> &getLoop() const;
};


#endif //TKOM_FOREACHLOOP_H
