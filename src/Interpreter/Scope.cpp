#include "Scope.h"

#include <utility>

void Scope::set_symbol(const std::string& name, std::unique_ptr<VariantValue> value_) {
    symbols[name] = std::move(value_);
}

const std::unique_ptr<VariantValue> & Scope::get_symbol(const std::string& name) {
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

