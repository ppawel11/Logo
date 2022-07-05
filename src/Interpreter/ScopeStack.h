#ifndef TKOM_SCOPESTACK_H
#define TKOM_SCOPESTACK_H

#include "Scope.h"
#include "CallContext.h"
#include "../Program/LanguageElements/Variables/Assignable.h"
#include "../Program/LanguageElements/Variables/String.h"
#include "../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../Program/LanguageElements/Variables/Bool.h"
#include "../Program/LanguageElements/Variables/Number.h"
#include "StandardLibrary/STD.h"
#include <variant>
#include <optional>
#include <stack>

class ScopeStack {
    std::stack<CallContext> call_stack;
    std::map<std::string, std::unique_ptr<FunctionDefinition>> func_map;

    std::optional<std::variant<Number, Bool, String, ListOfVariantValues>> last_result;

    bool returned;

public:
    bool isReturned() const;

    void setReturned(bool returned);

    ScopeStack(): last_result{ std::nullopt }, call_stack(), func_map( std::move( tkom::std_lib::init_functions() )), returned{ false } {

    }


    void init_global(std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs_);

    // Calls
    void make_call();
    void make_call(const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args);
    void return_call();

    // Scopes
    void make_scope();
    void make_scope(const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args);
    void end_scope();

    // Functions
    void make_func(const std::string &name, std::unique_ptr<FunctionDefinition> func_def);
    const std::unique_ptr<FunctionDefinition> & get_function(const std::string & name);

    // Variables
    void set_var(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value);
    std::variant<Number, Bool, String, ListOfVariantValues> get_var(const std::string& name);
    bool is_symbol_defined(const std::string& name);

    // Last result
    std::optional<std::variant<Number, Bool, String, ListOfVariantValues>> get_last_result() const;
    void set_last_result(std::variant<Number, Bool, String, ListOfVariantValues> lastResult);
};


#endif //TKOM_SCOPESTACK_H
