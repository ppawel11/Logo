#ifndef TKOM_EQUALITYEXECUTOR_H
#define TKOM_EQUALITYEXECUTOR_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"
#include "Caster.h"

class EqualityExecutor {
public:

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Number& lhs, const Number& rhs)
    {
        auto a = Bool( lhs.getValue() == rhs.getValue() );
        return a;
    }

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const Bool& lhs, const Bool& rhs)
    {
        return Bool( lhs.isValue() == rhs.isValue() );
    }

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const String& lhs, const String& rhs)
    {
        return Bool( lhs.getValue() == rhs.getValue() );
    }

    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const ListOfVariantValues& lhs, const ListOfVariantValues& rhs)
    {
        if( lhs.getElements().size() != rhs.getElements().size() )
            return Bool( false);

        for( int i = 0; i < lhs.getElements().size(); ++i )
        {
            if( !std::visit( Caster<bool> {}, std::visit(EqualityExecutor{}, lhs.getElements()[i], rhs.getElements()[i] ) ) )
                return Bool( false );
        }
        return Bool( true );
    }

    template<typename U, typename V>
    std::variant<Number, Bool, String, ListOfVariantValues> operator()(const U& lhs, const V &rhs)
    {
        throw std::runtime_error("invalid equality types");
    }
};

#endif //TKOM_EQUALITYEXECUTOR_H
