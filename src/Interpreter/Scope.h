#ifndef TKOM_SCOPE_H
#define TKOM_SCOPE_H

#include <map>
#include <string>
#include <utility>

#include "../Program/LanguageElements/FunctionDefinition.h"
#include "../Program/LanguageElements/Variables/Bool.h"
#include "../Program/LanguageElements/Variables/Number.h"
#include "../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../Program/LanguageElements/Variables/String.h"

class Scope {
    std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> symbols {};
public:
    Scope() = default;

    explicit Scope(std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> args): symbols{std::move(args)} {}

    void set_symbol(const std::string &name, const std::variant<Number, Bool, String, ListOfVariantValues> &value_ );

    std::variant<Number, Bool, String, ListOfVariantValues> get_symbol(const std::string& name );

    bool is_symbol_defined(const std::string& name );
};


#endif //TKOM_SCOPE_H
