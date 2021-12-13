#ifndef TKOM_LABEL_H
#define TKOM_LABEL_H


#include "Assignable.h"
#include <string>
#include <utility>

class Label: public Assignable {
    std::string label;
public:
    explicit Label(std::string label_): label{std::move(label_)}, Assignable() {}

    void be_evaluated(Interpreter *interpreter) override;

    const std::string &getLabel() const;
};


#endif //TKOM_LABEL_H
