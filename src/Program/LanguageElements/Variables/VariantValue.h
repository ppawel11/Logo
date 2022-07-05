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
    VariantValue() = default;
    virtual ~VariantValue() = default;

    virtual bool to_bool() = 0;
    virtual std::string to_string() = 0;
    virtual int to_number() = 0;
    virtual std::vector<std::shared_ptr<VariantValue>> to_list() = 0;

    virtual void set_value(bool value_) = 0;
    virtual void set_value(int value_) = 0;
    virtual void set_value(std::vector<std::shared_ptr<VariantValue>> value_) = 0;
    virtual void set_value(std::string value_) = 0;
    virtual void set_value(VariantValue* value_) = 0;
};

#endif //TKOM_VARIANTVALUE_H
