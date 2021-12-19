#include "ScopeStack.h"

#include <utility>

void ScopeStack::make_call() {
    call_stack.push(CallContext());
}

void ScopeStack::make_call(std::map<std::string, VariantValue *> args) {
    call_stack.push(CallContext(std::move(args)));
}

void ScopeStack::return_call() {
    call_stack.pop();
}

void ScopeStack::make_var(const std::string &name, VariantValue *value_) {
    if( !call_stack.empty() )
    {
        call_stack.top().set_variable(name, value_);
    }
    else
    {
        call_stack.top().set_variable(name, value_);
    }
}

VariantValue * ScopeStack::get_var(const std::string& name) {
    return nullptr;
}

void ScopeStack::set_var(const std::string& name, VariantValue *value) {
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

    last_returned = nullptr;
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

VariantValue * ScopeStack::get_last_returned() const {
    return last_returned;
}

void ScopeStack::set_last_returned(VariantValue *lastReturned) {
    last_returned = lastReturned;
}

VariantValue * ScopeStack::get_last_result() const {
    return last_result;
}

void ScopeStack::set_last_result(VariantValue *lastResult) {
    last_result = lastResult;
}

bool ScopeStack::is_symbol_defined(std::string name) {
    return false;
}
