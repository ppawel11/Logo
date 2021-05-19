#ifndef TKOM_FOREACHLOOP_H
#define TKOM_FOREACHLOOP_H

#include <string>
#include <utility>
#include <vector>
#include "LanguageElement.h"
#include "Block.h"

class ForEachLoop: public LanguageElement {
    std::string value_label;
    std::string container_label;
    Block loop;

public:
    ForEachLoop(std::string value_label_, std::string container_label_, Block loop_):
        value_label{std::move( value_label_ )},
        container_label{std::move( container_label_ )},
        loop{ loop_ } {}

    virtual void be_handled(Parser* parser) {}
};


#endif //TKOM_FOREACHLOOP_H
