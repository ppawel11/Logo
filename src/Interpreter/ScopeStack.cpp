#include "ScopeStack.h"

#include <utility>

void ScopeStack::make_call() {
    call_stack.push(CallContext());
}

void ScopeStack::make_call(std::map<std::string, std::unique_ptr<VariantValue>> args) {
    call_stack.push(CallContext(std::move(args)));
}

void ScopeStack::return_call() {
    call_stack.pop();
}

void ScopeStack::make_var(const std::string &name, std::unique_ptr<VariantValue> value_) {
    if( !call_stack.empty() )
    {
        call_stack.top().set_variable(name, value_);
    }
    else
    {
        call_stack.top().set_variable(name, value_);
    }
}

std::unique_ptr<VariantValue> & ScopeStack::get_var(const std::string& name) {
    //todo: odnajdywanie zmiennej na stosie scopów
    return last_result;
}

void ScopeStack::set_var(const std::string& name, std::unique_ptr<VariantValue> &value) {
    if( !call_stack.empty() )
    {
        call_stack.top().set_variable(name, value);
    }
    else
    {
        call_stack.top().set_variable(name, value);
    }
}

void ScopeStack::init_global(std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs_) {
    call_stack.push(CallContext());

    func_map = std::move(func_defs_);

    last_result = nullptr;
}

void ScopeStack::make_func(const std::string &name, std::unique_ptr<FunctionDefinition> func_def) {
     func_map[name] = std::move(func_def);
}

const std::unique_ptr<FunctionDefinition> & ScopeStack::get_function(const std::string &name) {
    if( func_map.find(name) != func_map.end() )
        return func_map.at(name);
    throw std::runtime_error("func not found");
}

std::unique_ptr<VariantValue> & ScopeStack::get_last_result() const {
    return last_result;
}

void ScopeStack::set_last_result(std::unique_ptr<VariantValue> lastResult) {
    last_result = std::move(lastResult);
}

bool ScopeStack::is_symbol_defined(std::string name) {
    // todo: odnalezienie zmiennej na stosie scopów
    return false;
}

const std::optional<std::variant<Number, Bool, String, ListOfVariantValues>> &ScopeStack::getLastResultVariant() const {
    return last_result_variant;
}

void ScopeStack::setLastResultVariant( const std::optional<std::variant<Number, Bool, String, ListOfVariantValues>> & lastResultVariant ) {
    last_result_variant = lastResultVariant;
}

