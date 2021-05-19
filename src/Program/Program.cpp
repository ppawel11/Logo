#include "Program.h"

#include <utility>

Program::Program(std::vector<LanguageElement *> statements_, std::map<std::string,
                 FunctionDefinition> func_definitions_) {
    instructions = std::move(statements_);
    func_definitions = std::move(func_definitions_);
}
