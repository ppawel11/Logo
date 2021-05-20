#ifndef TKOM_FUNCTIONDEFINITION_H
#define TKOM_FUNCTIONDEFINITION_H

#include "LanguageElement.h"
#include "Block.h"
#include <string>
#include <utility>
#include <vector>

class FunctionDefinition: public LanguageElement {
    std::string name;
    std::vector<std::string> parameters;
    Block body;

public:

    FunctionDefinition(std::string name_, std::vector<std::string> parameters_, Block body_):
            name{std::move( name_ )}, parameters{std::move( parameters_ )}, body{std::move( body_ )} {}

    void be_handled(Interpreter *interpreter) override {

    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        FunctionDefinition::name = name_;
    }

    const std::vector<std::string> &getParameters() const {
        return parameters;
    }

    void setParameters(const std::vector<std::string> &parameters_) {
        FunctionDefinition::parameters = parameters_;
    }

    const Block &getBody() const {
        return body;
    }

    void setBody(const Block &body_) {
        FunctionDefinition::body = body_;
    }
};


#endif //TKOM_FUNCTIONDEFINITION_H
