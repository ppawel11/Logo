#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <vector>
#include <string>
#include <map>

#include "LanguageElements/FunctionDefinition.h"
#include "LanguageElements/LanguageElement.h"

class Program {
    std::map<std::string, FunctionDefinition> func_definitions;
    std::vector<LanguageElement*> instructions;
public:
    Program(std::vector<LanguageElement *> statements_, std::map<std::string, FunctionDefinition> func_definitions_ );
};


#endif //TKOM_PROGRAM_H
