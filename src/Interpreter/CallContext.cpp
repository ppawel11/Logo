#include "CallContext.h"

#include <utility>

CallContext::CallContext() {
    scope_list.emplace_back(Scope());
}

CallContext::CallContext(std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> args) {
    scope_list.emplace_back(Scope(std::move(args)));
}

void CallContext::pop_block_scope() {
    scope_list.pop_back();
}

void CallContext::add_block_scope() {
    scope_list.emplace_back(Scope());
}

void CallContext::add_block_scope( const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args) {
    scope_list.emplace_back( Scope( args ) );
}

bool CallContext::is_symbol_declared(const std::string& name) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name))
            return true;
    }
    return false;
}

void CallContext::set_variable(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name)) {
            it->set_symbol(name, value);
            return;
        }
    }

    scope_list.rbegin()->set_symbol(name, value);
}

std::variant<Number, Bool, String, ListOfVariantValues> CallContext::get_variable(const std::string& name) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name)) {
            return it->get_symbol(name);
        }
    }

    throw std::runtime_error("symbol not defined");
}
