#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <utility>
#include <vector>
#include <string>
#include <map>

#include "LanguageElements/FunctionDefinition.h"
#include "LanguageElements/LanguageElement.h"

class Program {
public:
    std::vector<std::unique_ptr<LanguageElement>> instructions;
    std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs;

    explicit Program(std::vector<std::unique_ptr<LanguageElement>> statements_, std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs_)
            : instructions{std::move(statements_)}, func_defs{std::move(func_defs_)} {}

//    const std::vector<std::unique_ptr<LanguageElement>> &getInstructions() const;
//
//    void setInstructions(const std::vector<std::unique_ptr<LanguageElement>> &instructions);
//
//    std::map<std::string, std::unique_ptr<FunctionDefinition>> getFuncDefs();
//
//    void setFuncDefs(const std::map<std::string, std::unique_ptr<FunctionDefinition>> &funcDefs);
};

//const std::vector<std::unique_ptr<LanguageElement>> &Program::getInstructions() const {
//    return instructions;
//}
//
//void Program::setInstructions(const std::vector<std::unique_ptr<LanguageElement>> &instructions) {
//    Program::instructions = instructions;
//}
//
//std::map<std::string, std::unique_ptr<FunctionDefinition>> Program::getFuncDefs() {
//    return std::move(func_defs);
//}
//
//void Program::setFuncDefs(const std::map<std::string, std::unique_ptr<FunctionDefinition>> &funcDefs) {
//    func_defs = funcDefs;
//}


#endif //TKOM_PROGRAM_H
