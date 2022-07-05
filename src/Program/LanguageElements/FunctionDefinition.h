#ifndef TKOM_FUNCTIONDEFINITION_H
#define TKOM_FUNCTIONDEFINITION_H

#include "LanguageElement.h"
#include "Block.h"
#include "Variables/Assignable.h"
#include <string>
#include <utility>
#include <vector>

class Interpreter;

class FunctionDefinition: public LanguageElement {
    std::string name;
    std::vector<std::string> parameters;
    std::unique_ptr<LanguageElement> body;

public:

    FunctionDefinition(std::string name_, std::vector<std::string> parameters_, std::unique_ptr<LanguageElement> body_):
            name{std::move( name_ )}, parameters{std::move( parameters_ )}, body{ std::move(body_) } {}

    FunctionDefinition(FunctionDefinition&& func_def)
    {
        func_def.name = name;
        func_def.parameters = std::move(parameters);
        func_def.body = std::move(body);
    }

    void be_handled(LanguageElementVisitor *interpreter) override;

    const std::string &getName() const {
        return name;
    }
//
//    void setName(const std::string &name_) {
//        FunctionDefinition::name = name_;
//    }

    const std::vector<std::string> &getParameters() const {
        return parameters;
    }

//    void setParameters(const std::vector<std::string> &parameters_) {
//        FunctionDefinition::parameters = parameters_;
//    }

    const std::unique_ptr<LanguageElement> & getBody() const {
        return body;
    }

//    void setBody(LanguageElement *body) {
//        FunctionDefinition::body = body;
//    }
};


#endif //TKOM_FUNCTIONDEFINITION_H
