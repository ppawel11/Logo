#ifndef TKOM_CALLCONTEXT_H
#define TKOM_CALLCONTEXT_H

#include <list>
#include "Scope.h"

class CallContext {
    std::list<Scope> scope_list;
public:
    CallContext();

    CallContext(std::map<std::string, Assignable*> args);

    void pop_block_scope();
    void add_block_scope();
    void add_block_scope(std::map<std::string,Assignable*> args);

    bool is_symbol_declared(const std::string& name);
    void set_variable(const std::string& name, Assignable*);
    Assignable* get_variable(const std::string& name);


};


#endif //TKOM_CALLCONTEXT_H
