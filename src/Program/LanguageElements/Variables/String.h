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

    void be_evaluated(Interpreter *interpreter) override;

    VariantValue *operator+(VariantValue *other_value) override;
    VariantValue *operator+(String *other_value) override;
    VariantValue *operator+(Bool *other_value) override;
    VariantValue *operator+(Number *other_value) override;
    VariantValue *operator+(ListOfVariantValues *other_value) override;

    VariantValue *operator-(VariantValue *other_value) override;
    VariantValue *operator-(String *other_value) override;
    VariantValue *operator-(Bool *other_value) override;
    VariantValue *operator-(Number *other_value) override;
    VariantValue *operator-(ListOfVariantValues *other_value) override;

    VariantValue *operator/(VariantValue *other_value) override;
    VariantValue *operator/(String *other_value) override;
    VariantValue *operator/(Bool *other_value) override;
    VariantValue *operator/(Number *other_value) override;
    VariantValue *operator/(ListOfVariantValues *other_value) override;

    VariantValue *operator*(VariantValue *other_value) override;
    VariantValue *operator*(String *other_value) override;
    VariantValue *operator*(Bool *other_value) override;
    VariantValue *operator*(Number *other_value) override;
    VariantValue *operator*(ListOfVariantValues *other_value) override;

    VariantValue *operator&&(VariantValue *other_value) override;
    VariantValue *operator&&(Bool *other_value) override;
    VariantValue *operator&&(Number *other_value) override;
    VariantValue *operator&&(String *other_value) override;
    VariantValue *operator&&(ListOfVariantValues *other_value) override;

    VariantValue *operator||(VariantValue *other_value) override;
    VariantValue *operator||(String *other_value) override;
    VariantValue *operator||(Bool *other_value) override;
    VariantValue *operator||(Number *other_value) override;
    VariantValue *operator||(ListOfVariantValues *other_value) override;

    bool operator==(VariantValue *other_value) override;
    bool operator==(String *other_value) override;
    bool operator==(Bool *other_value) override;
    bool operator==(Number *other_value) override;
    bool operator==(ListOfVariantValues *other_value) override;

    bool operator!=(VariantValue *other_value) override;
    bool operator!=(String *other_value) override;
    bool operator!=(Bool *other_value) override;
    bool operator!=(Number *other_value) override;
    bool operator!=(ListOfVariantValues *other_value) override;

    bool operator<(VariantValue *other_value) override;
    bool operator<(String *other_value) override;
    bool operator<(Bool *other_value) override;
    bool operator<(Number *other_value) override;
    bool operator<(ListOfVariantValues *other_value) override;

    bool operator<=(VariantValue *other_value) override;
    bool operator<=(String *other_value) override;
    bool operator<=(Bool *other_value) override;
    bool operator<=(Number *other_value) override;
    bool operator<=(ListOfVariantValues *other_value) override;

    bool operator>(VariantValue *other_value) override;
    bool operator>(String *other_value) override;
    bool operator>(Bool *other_value) override;
    bool operator>(Number *other_value) override;
    bool operator>(ListOfVariantValues *other_value) override;

    bool operator>=(VariantValue *other_value) override;
    bool operator>=(String *other_value) override;
    bool operator>=(Bool *other_value) override;
    bool operator>=(Number *other_value) override;
    bool operator>=(ListOfVariantValues *other_value) override;


    bool to_bool() override;
    std::string to_string() override;
    int to_number() override;
    std::vector<VariantValue *> to_list() override;

    void set_value(VariantValue *value_) override;
    void set_value(bool value_) override;
    void set_value(int value_) override;
    void set_value(std::vector<VariantValue *> value_) override;
    void set_value(std::string value_) override;
};

#endif //TKOM_STRING_H
