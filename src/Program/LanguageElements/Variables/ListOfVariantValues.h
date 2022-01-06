#ifndef TKOM_LISTOFVARIANTVALUES_H
#define TKOM_LISTOFVARIANTVALUES_H

#include "Assignable.h"
#include "VariantValue.h"

#include <utility>
#include <vector>

class ListOfVariantValues: public Assignable, public VariantValue {
    std::vector<std::shared_ptr<VariantValue>> elements;

public:
    explicit ListOfVariantValues(std::vector<std::shared_ptr<VariantValue>> elements) : elements{std::move(elements )} {}
    ~ListOfVariantValues() = default;
    void be_evaluated(Interpreter *interpreter) override;

    bool to_bool() override;
    std::string to_string() override;
    int to_number() override;
    std::vector<std::shared_ptr<VariantValue>> to_list() override;

    void set_value(bool value_) override;
    void set_value(int value_) override;
    void set_value(std::vector<std::shared_ptr<VariantValue>> value_) override;
    void set_value(std::string value_) override;
    void set_value(VariantValue *value_) override;

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
};


#endif //TKOM_LISTOFVARIANTVALUES_H
