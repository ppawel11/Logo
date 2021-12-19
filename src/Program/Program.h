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
    std::vector<LanguageElement *> instructions;
    std::map<std::string, FunctionDefinition *> func_defs;

    explicit Program(std::vector<LanguageElement *> statements_, std::map<std::string, FunctionDefinition *> func_defs_)
            : instructions{std::move(statements_)}, func_defs{std::move(func_defs_)} {}
};


#endif //TKOM_PROGRAM_H
