#ifndef TKOM_SCOPE_H
#define TKOM_SCOPE_H

#include <map>
#include <string>
#include <utility>

#include "../Program/LanguageElements/FunctionDefinition.h"
#include "../Program/LanguageElements/Variables/VariantValue.h"

class Scope {
    std::map<std::string, std::unique_ptr<VariantValue>> symbols;
public:
    Scope() = default;;

    explicit Scope(std::map<std::string, std::unique_ptr<VariantValue>> args): symbols{std::move(args)} {}

    void set_symbol(const std::string& name, std::unique_ptr<VariantValue> value_ = nullptr);

    const std::unique_ptr<VariantValue> & get_symbol(const std::string& name );

    bool is_symbol_defined(const std::string& name );
};


#endif //TKOM_SCOPE_H
