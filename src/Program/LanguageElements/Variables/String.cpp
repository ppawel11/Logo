#include "String.h"
#include "../../../Interpreter/Interpreter.h"

void String::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

std::unique_ptr<VariantValue> String::operator+(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value + this;
    return result;
}

std::unique_ptr<VariantValue> String::operator+(String* other_value) {
    return std::make_unique<String>(other_value->to_string() + to_string() );
}

std::unique_ptr<VariantValue> String::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on string and bool");
}

std::unique_ptr<VariantValue> String::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on string and number");
}

std::unique_ptr<VariantValue> String::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on string and list");
}

std::unique_ptr<VariantValue> String::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on string and other value");
}

std::unique_ptr<VariantValue> String::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on string and string");
}

std::unique_ptr<VariantValue> String::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on string and bool");
}

std::unique_ptr<VariantValue> String::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on string and number");
}

std::unique_ptr<VariantValue> String::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on string and list");
}

std::unique_ptr<VariantValue> String::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on string and other value");
}

std::unique_ptr<VariantValue> String::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on string and string");
}

std::unique_ptr<VariantValue> String::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on string and bool");
}

std::unique_ptr<VariantValue> String::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on string and number");
}

std::unique_ptr<VariantValue> String::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on string and list");
}

std::unique_ptr<VariantValue> String::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on string and other value");
}

std::unique_ptr<VariantValue> String::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on string and string");
}

std::unique_ptr<VariantValue> String::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on string and bool");
}

std::unique_ptr<VariantValue> String::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on string and number");
}

std::unique_ptr<VariantValue> String::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on string and list");
}

std::unique_ptr<VariantValue> String::operator&&(const std::unique_ptr<VariantValue> & other_value) {
    throw std::runtime_error("invalid operation and on string and other value");
}

std::unique_ptr<VariantValue> String::operator&&(String* other_value) {
    throw std::runtime_error("invalid operation and on string and string");
}

std::unique_ptr<VariantValue> String::operator&&(Bool* other_value) {
    throw std::runtime_error("invalid operation and on string and bool");
}

std::unique_ptr<VariantValue> String::operator&&(Number* other_value) {
    throw std::runtime_error("invalid operation and on string and number");
}

std::unique_ptr<VariantValue> String::operator&&(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation and on string and list");
}

std::unique_ptr<VariantValue> String::operator||(VariantValue* other_value) {
    throw std::runtime_error("invalid operation or on string and other value");
}

std::unique_ptr<VariantValue> String::operator||(String* other_value) {
    throw std::runtime_error("invalid operation or on string and string");
}

std::unique_ptr<VariantValue> String::operator||(Bool* other_value) {
    throw std::runtime_error("invalid operation or on string and bool");
}

std::unique_ptr<VariantValue> String::operator||(Number* other_value) {
    throw std::runtime_error("invalid operation or on string and number");
}

std::unique_ptr<VariantValue> String::operator||(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation or on string and list");
}

bool String::to_bool() {
    throw std::runtime_error("string has no bool value");
}

std::string String::to_string() {
    return value;
}

int String::to_number() {
    throw std::runtime_error("string has no numeric value");
}

std::vector<std::shared_ptr<VariantValue>> String::to_list() {
    throw std::runtime_error("string has no list value");
}

void String::set_value(bool value_) {
    throw std::runtime_error("string has no bool value");
}

void String::set_value(int value_) {
    throw std::runtime_error("string has no int value");
}

void String::set_value(std::vector<std::shared_ptr<VariantValue>> value_) {
    throw std::runtime_error("string has no list value");
}

void String::set_value(std::string value_) {
    value = value_;
}

void String::set_value(VariantValue *value_) {
    value = value_->to_string();
}

std::unique_ptr<VariantValue> String::operator==(VariantValue* other_value) {
    return *other_value == this;
}

std::unique_ptr<VariantValue> String::operator==(String* other_value) {
    return std::make_unique<Bool>(to_string() == other_value->to_string());
}
std::unique_ptr<VariantValue> String::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

std::unique_ptr<VariantValue> String::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

std::unique_ptr<VariantValue> String::operator!=(String* other_value) {
    return std::make_unique<Bool>(to_string() != other_value->to_string());
}

std::unique_ptr<VariantValue> String::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

std::unique_ptr<VariantValue> String::operator<(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

std::unique_ptr<VariantValue> String::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

std::unique_ptr<VariantValue> String::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

std::unique_ptr<VariantValue> String::operator<=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

std::unique_ptr<VariantValue> String::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

std::unique_ptr<VariantValue> String::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

std::unique_ptr<VariantValue> String::operator>(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

std::unique_ptr<VariantValue> String::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

std::unique_ptr<VariantValue> String::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

std::unique_ptr<VariantValue> String::operator>=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

std::unique_ptr<VariantValue> String::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

std::unique_ptr<VariantValue> String::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

std::unique_ptr<VariantValue> String::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

std::unique_ptr<VariantValue> String::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}
