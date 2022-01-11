#include "Scope.h"

#include <utility>

void Scope::set_symbol(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value_) {
    auto it = symbols.find( name );
    if( it != symbols.end() )
    {
        it->second = value_;
    }
    else
    {
        symbols.insert( {name, value_} );
    }
}

std::variant<Number, Bool, String, ListOfVariantValues> Scope::get_symbol(const std::string& name) {
    if( is_symbol_defined(name) )
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


