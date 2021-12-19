#ifndef TKOM_SCOPESTACK_H
#define TKOM_SCOPESTACK_H

#include "Scope.h"
#include "CallContext.h"
#include "../Program/LanguageElements/Variables/Assignable.h"
#include "../Program/LanguageElements/Variables/String.h"
#include "../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../Program/LanguageElements/Variables/Bool.h"
#include "../Program/LanguageElements/Variables/Number.h"
#include <variant>
#include <optional>
#include <stack>

class ScopeStack {
    // todo: DONE stos callcontextow
    // todo: DONE to nie assignable tylko varvalue

    std::stack<CallContext> call_stack;
    std::map<std::string, FunctionDefinition*> func_map;

    VariantValue* last_returned;
    VariantValue* last_result;
public:
    ScopeStack(): last_returned{ nullptr }, last_result{ nullptr }, call_stack(), func_map() {}

    void init_global(std::map<std::string, FunctionDefinition *> func_defs_);
    void make_call();
    void make_call(std::map<std::string, VariantValue *> args);
    void return_call();
    void make_var(const std::string &name, VariantValue *value_);
    void make_func(const std::string &name, FunctionDefinition func_def);
    FunctionDefinition * get_function(const std::string & name);
    VariantValue * get_var(const std::string& name);
    void set_var(const std::string& name, VariantValue *value);

    bool is_symbol_defined(std::string name);

    VariantValue * get_last_returned() const;

    void set_last_returned(VariantValue *lastReturned);

    VariantValue * get_last_result() const;

    void set_last_result(VariantValue *lastResult);
};


#endif //TKOM_SCOPESTACK_H
