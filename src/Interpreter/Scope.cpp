#include "Scope.h"

#include <utility>

void Scope::set_symbol(const std::string& name, VariantValue *value_) {
    symbols[name] = value_;
}

VariantValue * Scope::get_symbol(const std::string& name) {
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
    return symbols.find(name) != symbols.end();
}

