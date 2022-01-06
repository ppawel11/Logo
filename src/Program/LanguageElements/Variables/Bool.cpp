#include "Bool.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Bool::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

std::unique_ptr<VariantValue> Bool::operator+(VariantValue* other_value) {
    throw std::runtime_error("invalid operation addition on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on bool and list");
}

std::unique_ptr<VariantValue> Bool::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and list");
}

std::unique_ptr<VariantValue> Bool::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on bool and list");
}

std::unique_ptr<VariantValue> Bool::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and list");
}

std::unique_ptr<VariantValue> Bool::operator&&(const std::unique_ptr<VariantValue>& other_value) {
    return std::move(*other_value && this);
//    return result;
}

std::unique_ptr<VariantValue> Bool::operator&&(String* other_value) {
    if( value && !other_value->to_string().empty() )
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator&&(Bool* other_value) {
    if( value && other_value->to_bool() )
        return std::move(std::make_unique<Bool>(true));
    return std::move(std::make_unique<Bool>(false));
}

std::unique_ptr<VariantValue> Bool::operator&&(Number* other_value) {
    if( value && (other_value->to_number() > 0))
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator&&(ListOfVariantValues* other_value) {
    if( value && !other_value->to_list().empty())
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator||(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result =* other_value || this;
    return result;
}

std::unique_ptr<VariantValue> Bool::operator||(String* other_value) {
    if( value || !other_value->to_string().empty() )
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator||(Bool* other_value) {
    if( value || other_value->to_bool() )
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator||(Number* other_value) {
    if( value || (other_value->to_number() > 0))
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

std::unique_ptr<VariantValue> Bool::operator||(ListOfVariantValues* other_value) {
    if( value || !other_value->to_list().empty())
        return std::make_unique<Bool>(true);
    return std::make_unique<Bool>(false);
}

bool Bool::to_bool() {
    return value;
}

std::string Bool::to_string() {
    std::string result = value ? "True" : "False";
    return result;
}

int Bool::to_number() {
    throw std::runtime_error("bool has no string value");
}

std::vector<std::shared_ptr<VariantValue>> Bool::to_list() {
    throw std::runtime_error("bool has no list value");
}

void Bool::set_value(bool value_) {
    value = value_;
}

void Bool::set_value(int value_) {
    throw std::runtime_error("bool has no int value");
}

void Bool::set_value(std::vector<std::shared_ptr<VariantValue>> value_) {
    throw std::runtime_error("bool has no list value");
}

void Bool::set_value(std::string value_) {
    throw std::runtime_error("bool has no string value");
}

void Bool::set_value(VariantValue *value_) {
    value = value_->to_bool();
}

std::unique_ptr<VariantValue> Bool::operator==(VariantValue* other_value) {
    return *other_value == this;
}

std::unique_ptr<VariantValue> Bool::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator==(Bool* other_value) {
    return std::make_unique<Bool>(value == other_value->to_bool());
}

std::unique_ptr<VariantValue> Bool::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

std::unique_ptr<VariantValue> Bool::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

std::unique_ptr<VariantValue> Bool::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator!=(Bool* other_value) {
    return std::make_unique<Bool>(value != other_value->to_bool());
}

std::unique_ptr<VariantValue> Bool::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

std::unique_ptr<VariantValue> Bool::operator<(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

std::unique_ptr<VariantValue> Bool::operator<=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and pther value");
}

std::unique_ptr<VariantValue> Bool::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

std::unique_ptr<VariantValue> Bool::operator>(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

std::unique_ptr<VariantValue> Bool::operator>=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

std::unique_ptr<VariantValue> Bool::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

std::unique_ptr<VariantValue> Bool::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

std::unique_ptr<VariantValue> Bool::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

std::unique_ptr<VariantValue> Bool::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}
