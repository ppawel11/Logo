#ifndef TKOM_STRING_H
#define TKOM_STRING_H

#include "Assignable.h"
#include "VariantValue.h"

#include <string>
#include <utility>

class String: public Assignable, public VariantValue {
    std::string value;
public:
    explicit String( std::string value_ ): value{std::move(value_)}, Assignable() {}
    ~String() = default;
    void be_evaluated(Interpreter *interpreter) override;

    std::unique_ptr<VariantValue> operator+(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator+(String *other_value) override;
    std::unique_ptr<VariantValue> operator+(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator+(Number *other_value) override;
    std::unique_ptr<VariantValue> operator+(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator-(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator-(String *other_value) override;
    std::unique_ptr<VariantValue> operator-(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator-(Number *other_value) override;
    std::unique_ptr<VariantValue> operator-(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator/(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator/(String *other_value) override;
    std::unique_ptr<VariantValue> operator/(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator/(Number *other_value) override;
    std::unique_ptr<VariantValue> operator/(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator*(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator*(String *other_value) override;
    std::unique_ptr<VariantValue> operator*(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator*(Number *other_value) override;
    std::unique_ptr<VariantValue> operator*(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator&&(const std::unique_ptr<VariantValue> & other_value) override;
    std::unique_ptr<VariantValue> operator&&(Bool* other_value) override;
    std::unique_ptr<VariantValue> operator&&(Number *other_value) override;
    std::unique_ptr<VariantValue> operator&&(String *other_value) override;
    std::unique_ptr<VariantValue> operator&&(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator||(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator||(String *other_value) override;
    std::unique_ptr<VariantValue> operator||(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator||(Number *other_value) override;
    std::unique_ptr<VariantValue> operator||(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator==(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator==(String *other_value) override;
    std::unique_ptr<VariantValue> operator==(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator==(Number *other_value) override;
    std::unique_ptr<VariantValue> operator==(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator!=(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator!=(String *other_value) override;
    std::unique_ptr<VariantValue> operator!=(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator!=(Number *other_value) override;
    std::unique_ptr<VariantValue> operator!=(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator<(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator<(String *other_value) override;
    std::unique_ptr<VariantValue> operator<(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator<(Number *other_value) override;
    std::unique_ptr<VariantValue> operator<(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator<=(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator<=(String *other_value) override;
    std::unique_ptr<VariantValue> operator<=(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator<=(Number *other_value) override;
    std::unique_ptr<VariantValue> operator<=(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator>(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator>(String *other_value) override;
    std::unique_ptr<VariantValue> operator>(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator>(Number *other_value) override;
    std::unique_ptr<VariantValue> operator>(ListOfVariantValues *other_value) override;

    std::unique_ptr<VariantValue> operator>=(VariantValue *other_value) override;
    std::unique_ptr<VariantValue> operator>=(String *other_value) override;
    std::unique_ptr<VariantValue> operator>=(Bool *other_value) override;
    std::unique_ptr<VariantValue> operator>=(Number *other_value) override;
    std::unique_ptr<VariantValue> operator>=(ListOfVariantValues *other_value) override;


    bool to_bool() override;
    std::string to_string() override;
    int to_number() override;
    std::vector<std::shared_ptr<VariantValue>> to_list() override;

    void set_value(VariantValue *value_) override;
    void set_value(bool value_) override;
    void set_value(int value_) override;
    void set_value(std::vector<std::shared_ptr<VariantValue>> value_) override;
    void set_value(std::string value_) override;
};

#endif //TKOM_STRING_H
