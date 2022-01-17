#ifndef TKOM_OREXECUTOR_H
#define TKOM_OREXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

class OrExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Bool& lhs, const Bool& rhs)
    {
        return Bool(lhs.isValue() || rhs.isValue());
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid or types");
    }
};

#endif //TKOM_OREXECUTOR_H
