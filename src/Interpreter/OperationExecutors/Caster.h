#ifndef TKOM_CASTER_H
#define TKOM_CASTER_H

#include <variant>
#include <system_error>
#include "../../Program/LanguageElements/Variables/Number.h"
#include "../../Program/LanguageElements/Variables/Bool.h"
#include "../../Program/LanguageElements/Variables/ListOfVariantValues.h"
#include "../../Program/LanguageElements/Variables/String.h"

template<typename T> class Caster;

template<>
class Caster<int> {
public:

    int operator()(const Number& casted )
    {
        return casted.getValue();
    }

    template<typename U>
    int operator()(const U& casted )
    {
        throw std::runtime_error("invalid type to int conversion");
    }
};

template<>
class Caster<std::string> {
public:

    std::string operator()(const String& casted )
    {
        return casted.getValue();
    }

    std::string operator()(const Bool& casted )
    {
        if( casted.isValue() )
            return "True";
        return "False";
    }

    std::string operator()(const Number& casted )
    {
        return std::to_string( casted.getValue() );
    }

    template<typename U>
    std::string operator()(const U& casted )
    {
        throw std::runtime_error("invalid type to string conversion");
    }
};

template<>
class Caster<bool> {
public:

    bool operator()(const Bool& casted )
    {
        return casted.isValue();
    }

    template<typename U>
    bool operator()(const U& casted )
    {
        throw std::runtime_error("invalid type to bool conversion");
    }
};

template<>
class Caster<std::vector<std::variant<Number, Bool, String, ListOfVariantValues>>> {
public:

    std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> operator()(const ListOfVariantValues& casted )
    {
        return casted.getElements();
    }

    template<typename U>
    std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> operator()(const U& casted )
    {
        throw std::runtime_error("invalid type to std::vector<std::variant<Number, Bool, String, ListOfVariantValues>> conversion");
    }
};

#endif //TKOM_CASTER_H
