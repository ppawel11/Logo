#ifndef TKOM_MULTIPLICATIONEXECUTOR_H
#define TKOM_MULTIPLICATIONEXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

class MultiplicationExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Number& lhs, const Number& rhs)
    {
        return Number( lhs.getValue() * rhs.getValue() );
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid multiply types");
    }
};

#endif //TKOM_MULTIPLICATIONEXECUTOR_H
