#ifndef TKOM_SCOPESTACK_H
#define TKOM_SCOPESTACK_H

#include "Scope.h"
#include "../Program/LanguageElements/Variables/Assignable.h"
#include "../Program/LanguageElements/Variables/String.h"
#include "../Program/LanguageElements/Variables/List.h"
#include "../Program/LanguageElements/Variables/Bool.h"
#include "../Program/LanguageElements/Variables/Number.h"
#include <variant>
#include <optional>
#include <stack>

class ScopeStack {
    Scope global;
    std::stack<Scope> stack;
    std::optional<std::variant<std::string, int, bool, std::vector<Assignable*>>> last_returned;
    std::optional<std::variant<std::string, int, bool, std::vector<Assignable*>>> last_result;
public:
    ScopeStack(): last_returned{ std::nullopt }, last_result{ std::nullopt } {}
    void init_global(std::map<std::string, FunctionDefinition> func_defs_);
    void make_call();
    void make_call(std::map<std::string, Assignable*> args);
    void return_call();
    void make_var(const std::string &name, Assignable *value_);
    void make_func(const std::string &name, FunctionDefinition func_def);
    FunctionDefinition * get_function(const std::string & name);
    Assignable * get_var(const std::string& name);
    void set_var(const std::string& name, Assignable* value);

    bool is_symbol_defined(std::string name);

    std::optional<std::variant<std::string, int, bool, std::vector<Assignable *>>> get_last_returned() const;

    void set_last_returned(std::variant<std::string, int, bool, std::vector<Assignable *>> lastReturned);

    std::optional<std::variant<std::string, int, bool, std::vector<Assignable *>>> get_last_result() const;

    void set_last_result(std::variant<std::string, int, bool, std::vector<Assignable *>> lastResult);
};


#endif //TKOM_SCOPESTACK_H
