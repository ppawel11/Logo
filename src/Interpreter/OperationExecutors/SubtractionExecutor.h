#ifndef TKOM_SUBTRACTIONEXECUTOR_H
#define TKOM_SUBTRACTIONEXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

class SubtractionExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Number& lhs, const Number& rhs)
    {
        return Number( lhs.getValue() - rhs.getValue() );
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid substraction types");
    }
};


#endif //TKOM_SUBTRACTIONEXECUTOR_H
