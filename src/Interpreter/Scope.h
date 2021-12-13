#ifndef TKOM_SCOPE_H
#define TKOM_SCOPE_H

#include <map>
#include <string>

#include "../Program/LanguageElements/FunctionDefinition.h"
#include "../Program/LanguageElements/Variables/Assignable.h"

class Scope {
    std::map<std::string, Assignable*> symbols;
public:
    Scope() {};

    Scope(std::map<std::string, Assignable*> args): symbols{args} {}

    void set_symbol(const std::string& name, Assignable *value_ = nullptr);

    Assignable * get_symbol(const std::string& name );

    bool is_symbol_defined(const std::string& name );
};


#endif //TKOM_SCOPE_H
