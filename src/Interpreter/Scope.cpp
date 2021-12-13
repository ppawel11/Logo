#include "Scope.h"

#include <utility>

void Scope::set_symbol(const std::string& name, Assignable *value_) {
    symbols[name] = value_;
}

Assignable * Scope::get_symbol(const std::string& name) {
    if(is_symbol_defined(name) )
    {
        return symbols[name];
    }
    else
    {
        throw std::runtime_error("variable not found");
    }
}

bool Scope::is_symbol_defined(const std::string& name) {
    auto it = symbols.find(name);
    return it != symbols.end();
}

