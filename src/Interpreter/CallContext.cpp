#include "CallContext.h"

#include <utility>

CallContext::CallContext() {
    scope_list.emplace_back(Scope());
}

CallContext::CallContext(std::map<std::string, VariantValue *> args) {
    scope_list.emplace_back(Scope(std::move(args)));
}

void CallContext::pop_block_scope() {
    scope_list.pop_back();
}

void CallContext::add_block_scope() {
    scope_list.emplace_back(Scope());
}

void CallContext::add_block_scope(std::map<std::string, VariantValue *> args) {
    scope_list.emplace_back(std::move(args));
}

bool CallContext::is_symbol_declared(const std::string& name) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name))
            return true;
    }
    return false;
}

void CallContext::set_variable(const std::string& name, VariantValue* value) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name)) {
            it->set_symbol(name, value);
            return;
        }
    }

    scope_list.end()->set_symbol(name, value);
}

VariantValue* CallContext::get_variable(const std::string& name) {
    for( auto it = scope_list.rbegin(); it != scope_list.rend(); it++)
    {
        if(it->is_symbol_defined(name)) {
            return it->get_symbol(name);
        }
    }

    throw std::runtime_error("symbol not defined");
}
