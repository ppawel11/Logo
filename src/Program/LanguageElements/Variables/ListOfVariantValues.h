#ifndef TKOM_LISTOFVARIANTVALUES_H
#define TKOM_LISTOFVARIANTVALUES_H

#include "Assignable.h"
#include "VariantValue.h"

#include <utility>
#include <vector>

class ListOfVariantValues: public Assignable, public VariantValue {
    std::vector<VariantValue*> elements;

public:
    explicit ListOfVariantValues(std::vector<VariantValue *> elements) : elements{std::move(elements )} {}

    void be_evaluated(Interpreter *interpreter) override;

    bool to_bool() override;
    std::string to_string() override;
    int to_number() override;
    std::vector<VariantValue *> to_list() override;

    void set_value(bool value_) override;
    void set_value(int value_) override;
    void set_value(std::vector<VariantValue *> value_) override;
    void set_value(std::string value_) override;
    void set_value(VariantValue *value_) override;

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
};


#endif //TKOM_LISTOFVARIANTVALUES_H
