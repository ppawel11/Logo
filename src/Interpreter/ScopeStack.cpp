#include "ScopeStack.h"

#include <utility>

void ScopeStack::make_call() {
    call_stack.push(CallContext());
}

void ScopeStack::make_call(const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args) {
    call_stack.push( CallContext(args) );
}

void ScopeStack::return_call() {
    call_stack.pop();
}

std::variant<Number, Bool, String, ListOfVariantValues> ScopeStack::get_var(const std::string& name) {
    return call_stack.top().get_variable( name );
}

void ScopeStack::set_var(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value) {
    call_stack.top().set_variable( name, value );
}

void ScopeStack::init_global(std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs_) {
    call_stack.push( CallContext() );

    func_map = std::move( func_defs_ );

    last_result = std::nullopt;
}

void ScopeStack::make_func(const std::string &name, std::unique_ptr<FunctionDefinition> func_def) {
     func_map[name] = std::move(func_def);
}

const std::unique_ptr<FunctionDefinition> & ScopeStack::get_function(const std::string &name) {
    if( func_map.find(name) != func_map.end() )
        return func_map.at(name);
    throw std::runtime_error("func not found");
}

std::optional<std::variant<Number, Bool, String, ListOfVariantValues>> ScopeStack::get_last_result() const {
    return last_result;
}

void ScopeStack::set_last_result(std::variant<Number, Bool, String, ListOfVariantValues> lastResult) {
    last_result = lastResult;
}

bool ScopeStack::is_symbol_defined(const std::string& name) {
    return call_stack.top().is_symbol_declared( name );
}

void ScopeStack::make_scope() {
    call_stack.top().add_block_scope();
}

void ScopeStack::make_scope(const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args) {
    call_stack.top().add_block_scope( args );
}

void ScopeStack::end_scope() {
    call_stack.top().pop_block_scope();
}

bool ScopeStack::isReturned() const {
    return returned;
}

void ScopeStack::setReturned(bool returned) {
    ScopeStack::returned = returned;
}

