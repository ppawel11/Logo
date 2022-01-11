#ifndef TKOM_ANDEXECUTOR_H
#define TKOM_ANDEXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

class AndExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Bool& lhs, const Bool &rhs)
    {
        return Bool( lhs.isValue() && rhs.isValue() );
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid and types");
    }
};

#endif //TKOM_ANDEXECUTOR_H
