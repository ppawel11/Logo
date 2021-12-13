#include "ScopeStack.h"

#include <utility>

void ScopeStack::make_call() {
    stack.push(Scope());
}

void ScopeStack::make_call(std::map<std::string, Assignable *> args) {
    stack.push(Scope(std::move(args)));
}

void ScopeStack::return_call() {
    stack.pop();
}

void ScopeStack::make_var(const std::string &name, Assignable *value_) {
    if( !stack.empty() )
    {
        stack.top().set_symbol(name, value_);
    }
    else
    {
        global.set_symbol(name, value_);
    }
}

Assignable * ScopeStack::get_var(const std::string& name) {

}

void ScopeStack::set_var(const std::string& name, Assignable *value) {
    if( !stack.empty() )
    {
        stack.top().set_symbol(name);
    }
    else
    {
        global.set_symbol(name);
    }
}

void ScopeStack::init_global(std::map<std::string, FunctionDefinition> func_defs_) {
    for(auto & func_def : func_defs_)
    {
            global.set_symbol(func_def.first, static_cast<Assignable*>(&func_def.second));
    }
    last_returned = nullptr;
    last_result = nullptr;
}

void ScopeStack::make_func(const std::string &name, FunctionDefinition func_def) {
     global.set_symbol( name, static_cast<Assignable*>(&func_def) );
}

FunctionDefinition * ScopeStack::get_function(const std::string &name) {
    return dynamic_cast<FunctionDefinition*>(global.get_symbol(name));
}

std::optional<std::variant<std::string, int, bool, std::vector<Assignable *>>> ScopeStack::get_last_returned() const {
    return last_returned;
}

void ScopeStack::set_last_returned(std::variant<std::string, int, bool, std::vector<Assignable *>> lastReturned) {
    last_returned = lastReturned;
}

std::optional<std::variant<std::string, int, bool, std::vector<Assignable *>>> ScopeStack::get_last_result() const {
    return last_result;
}

void ScopeStack::set_last_result(std::variant<std::string, int, bool, std::vector<Assignable *>> lastResult) {
    last_result = lastResult;
}

bool ScopeStack::is_symbol_defined(std::string name) {
    return false;
}
