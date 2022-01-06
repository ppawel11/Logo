#ifndef TKOM_VARIANTVALUE_H
#define TKOM_VARIANTVALUE_H

#include <string>
#include <vector>
#include <memory>

class Bool;
class ListOfVariantValues;
class Number;
class String;

class VariantValue {
public:
    virtual ~VariantValue() = default;
    virtual std::unique_ptr<VariantValue> operator+(VariantValue *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator+(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator+(Bool *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator+(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator+(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator-(VariantValue *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator-(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator-(Bool *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator-(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator-(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator/(VariantValue *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator/(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator/(Bool *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator/(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator/(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator*(VariantValue *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator*(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator*(Bool *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator*(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator*(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator&&(const std::unique_ptr<VariantValue> & other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator&&(Bool* other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator&&(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator&&(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator&&(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator||(VariantValue *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator||(String *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator||(Bool *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator||(Number *other_value) = 0;
    virtual std::unique_ptr<VariantValue> operator||(ListOfVariantValues *other_value) = 0;

    virtual std::unique_ptr<VariantValue> operator==(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator==(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator==(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator==(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator==(ListOfVariantValues * other_value ) = 0;

    virtual std::unique_ptr<VariantValue> operator!=(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator!=(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator!=(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator!=(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator!=(ListOfVariantValues * other_value ) = 0;

    virtual std::unique_ptr<VariantValue> operator<(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<(ListOfVariantValues * other_value ) = 0;

    virtual std::unique_ptr<VariantValue> operator<=(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<=(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<=(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<=(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator<=(ListOfVariantValues * other_value ) = 0;

    virtual std::unique_ptr<VariantValue> operator>(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>(ListOfVariantValues * other_value ) = 0;

    virtual std::unique_ptr<VariantValue> operator>=(VariantValue * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>=(String * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>=(Bool * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>=(Number * other_value ) = 0;
    virtual std::unique_ptr<VariantValue> operator>=(ListOfVariantValues * other_value ) = 0;

    virtual bool to_bool() = 0;
    virtual std::string to_string() = 0;
    virtual int to_number() = 0;
    virtual std::vector<std::shared_ptr<VariantValue>> to_list() = 0;

    virtual void set_value(bool value_) = 0;
    virtual void set_value(int value_) = 0;
    virtual void set_value(std::vector<std::shared_ptr<VariantValue>> value_) = 0;
    virtual void set_value(std::string value_) = 0;
    virtual void set_value(VariantValue* value_) = 0;

//    friend std::unique_ptr<VariantValue> operator+( const std::unique_ptr<VariantValue> & left_val, const std::unique_ptr<VariantValue> & right_val );
};

#endif //TKOM_VARIANTVALUE_H
