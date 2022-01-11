#ifndef TKOM_GREATEREXECUTOR_H
#define TKOM_GREATEREXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

class GreaterExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Number& lhs, const Number& rhs)
    {
        return Bool( lhs.getValue() > rhs.getValue() );
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid greater types");
    }
};

#endif //TKOM_GREATEREXECUTOR_H
