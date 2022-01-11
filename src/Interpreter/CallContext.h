#ifndef TKOM_CALLCONTEXT_H
#define TKOM_CALLCONTEXT_H

#include <list>
#include "Scope.h"

class CallContext {
    std::list<Scope> scope_list;
public:
    CallContext();

    explicit CallContext(std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> args);

    void pop_block_scope();
    void add_block_scope();
    void add_block_scope(const std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> &args);

    bool is_symbol_declared(const std::string& name);
    void set_variable(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value);
    std::variant<Number, Bool, String, ListOfVariantValues> get_variable(const std::string& name);


};


#endif //TKOM_CALLCONTEXT_H
