#ifndef TKOM_NUMBER_H
#define TKOM_NUMBER_H


#include "Assignable.h"
#include "VariantValue.h"

class Number: public Assignable, public VariantValue {
    int value;

public:
    explicit Number(int value_): value{value_}, Assignable() {}

    void be_evaluated(Interpreter* interpreter) override;

    bool to_bool() override;
    std::string to_string() override;
    int to_number() override;
    std::vector<VariantValue *> to_list() override;

    void set_value(bool value_) override;
    void set_value(int value_) override;
    void set_value(std::vector<VariantValue *> value_) override;
    void set_value(std::string value_) override;
    void set_value(VariantValue *value_) override;

    VariantValue* operator+(VariantValue* other_value) override;
    VariantValue* operator+(String* other_value) override;
    VariantValue* operator+(Bool* other_value) override;
    VariantValue* operator+(Number* other_value) override;
    VariantValue* operator+(ListOfVariantValues* other_value) override;

    VariantValue* operator-(VariantValue* other_value) override;
    VariantValue* operator-(String* other_value) override;
    VariantValue* operator-(Bool* other_value) override;
    VariantValue* operator-(Number* other_value) override;
    VariantValue* operator-(ListOfVariantValues* other_value) override;

    VariantValue* operator/(VariantValue* other_value) override;
    VariantValue* operator/(String* other_value) override;
    VariantValue* operator/(Bool* other_value) override;
    VariantValue* operator/(Number* other_value) override;
    VariantValue* operator/(ListOfVariantValues* other_value) override;

    VariantValue* operator*(VariantValue* other_value) override;
    VariantValue* operator*(String* other_value) override;
    VariantValue* operator*(Bool* other_value) override;
    VariantValue* operator*(Number* other_value) override;
    VariantValue* operator*(ListOfVariantValues* other_value) override;

    VariantValue* operator&&(VariantValue* other_value) override;
    VariantValue* operator&&(Bool* other_value) override;
    VariantValue* operator&&(Number* other_value) override;
    VariantValue* operator&&(String* other_value) override;
    VariantValue* operator&&(ListOfVariantValues* other_value) override;

    VariantValue* operator||(VariantValue* other_value) override;
    VariantValue* operator||(String* other_value) override;
    VariantValue* operator||(Bool* other_value) override;
    VariantValue* operator||(Number* other_value) override;
    VariantValue* operator||(ListOfVariantValues* other_value) override;

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
};


#endif //TKOM_NUMBER_H
