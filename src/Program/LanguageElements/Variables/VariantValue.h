#ifndef TKOM_VARIANTVALUE_H
#define TKOM_VARIANTVALUE_H

#include <string>
#include <vector>

class Bool;
class ListOfVariantValues;
class Number;
class String;

class VariantValue {
public:
    virtual VariantValue* operator+(VariantValue *other_value) = 0;
    virtual VariantValue* operator+(String *other_value) = 0;
    virtual VariantValue* operator+(Bool *other_value) = 0;
    virtual VariantValue* operator+(Number *other_value) = 0;
    virtual VariantValue* operator+(ListOfVariantValues *other_value) = 0;

    virtual VariantValue* operator-(VariantValue *other_value) = 0;
    virtual VariantValue* operator-(String *other_value) = 0;
    virtual VariantValue* operator-(Bool *other_value) = 0;
    virtual VariantValue* operator-(Number *other_value) = 0;
    virtual VariantValue* operator-(ListOfVariantValues *other_value) = 0;

    virtual VariantValue* operator/(VariantValue *other_value) = 0;
    virtual VariantValue* operator/(String *other_value) = 0;
    virtual VariantValue* operator/(Bool *other_value) = 0;
    virtual VariantValue* operator/(Number *other_value) = 0;
    virtual VariantValue* operator/(ListOfVariantValues *other_value) = 0;

    virtual VariantValue* operator*(VariantValue *other_value) = 0;
    virtual VariantValue* operator*(String *other_value) = 0;
    virtual VariantValue* operator*(Bool *other_value) = 0;
    virtual VariantValue* operator*(Number *other_value) = 0;
    virtual VariantValue* operator*(ListOfVariantValues *other_value) = 0;

    virtual VariantValue* operator&&(VariantValue *other_value) = 0;
    virtual VariantValue* operator&&(Bool *other_value) = 0;
    virtual VariantValue* operator&&(Number *other_value) = 0;
    virtual VariantValue* operator&&(String *other_value) = 0;
    virtual VariantValue* operator&&(ListOfVariantValues *other_value) = 0;

    virtual VariantValue* operator||(VariantValue *other_value) = 0;
    virtual VariantValue* operator||(String *other_value) = 0;
    virtual VariantValue* operator||(Bool *other_value) = 0;
    virtual VariantValue* operator||(Number *other_value) = 0;
    virtual VariantValue* operator||(ListOfVariantValues *other_value) = 0;

    virtual bool operator==(VariantValue * other_value ) = 0;
    virtual bool operator==(String * other_value ) = 0;
    virtual bool operator==(Bool * other_value ) = 0;
    virtual bool operator==(Number * other_value ) = 0;
    virtual bool operator==(ListOfVariantValues * other_value ) = 0;

    virtual bool operator!=(VariantValue * other_value ) = 0;
    virtual bool operator!=(String * other_value ) = 0;
    virtual bool operator!=(Bool * other_value ) = 0;
    virtual bool operator!=(Number * other_value ) = 0;
    virtual bool operator!=(ListOfVariantValues * other_value ) = 0;

    virtual bool operator<(VariantValue * other_value ) = 0;
    virtual bool operator<(String * other_value ) = 0;
    virtual bool operator<(Bool * other_value ) = 0;
    virtual bool operator<(Number * other_value ) = 0;
    virtual bool operator<(ListOfVariantValues * other_value ) = 0;

    virtual bool operator<=(VariantValue * other_value ) = 0;
    virtual bool operator<=(String * other_value ) = 0;
    virtual bool operator<=(Bool * other_value ) = 0;
    virtual bool operator<=(Number * other_value ) = 0;
    virtual bool operator<=(ListOfVariantValues * other_value ) = 0;

    virtual bool operator>(VariantValue * other_value ) = 0;
    virtual bool operator>(String * other_value ) = 0;
    virtual bool operator>(Bool * other_value ) = 0;
    virtual bool operator>(Number * other_value ) = 0;
    virtual bool operator>(ListOfVariantValues * other_value ) = 0;

    virtual bool operator>=(VariantValue * other_value ) = 0;
    virtual bool operator>=(String * other_value ) = 0;
    virtual bool operator>=(Bool * other_value ) = 0;
    virtual bool operator>=(Number * other_value ) = 0;
    virtual bool operator>=(ListOfVariantValues * other_value ) = 0;

    virtual bool to_bool() = 0;
    virtual std::string to_string() = 0;
    virtual int to_number() = 0;
    virtual std::vector<VariantValue *> to_list() = 0;

    virtual void set_value(bool value_) = 0;
    virtual void set_value(int value_) = 0;
    virtual void set_value(std::vector<VariantValue*> value_) = 0;
    virtual void set_value(std::string value_) = 0;
    virtual void set_value(VariantValue* value_) = 0;
};


#endif //TKOM_VARIANTVALUE_H
