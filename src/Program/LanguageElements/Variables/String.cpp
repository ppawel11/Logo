#include "String.h"
#include "../../../Interpreter/Interpreter.h"

void String::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

VariantValue* String::operator+(VariantValue* other_value) {
    VariantValue* result = *other_value + this;
    return result;
}

VariantValue* String::operator+(String* other_value) {
    return new String(other_value->to_string() + to_string() );
}

VariantValue* String::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on string and bool");
}

VariantValue* String::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on string and number");
}

VariantValue* String::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on string and list");
}

VariantValue* String::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on string and other value");
}

VariantValue* String::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on string and string");
}

VariantValue* String::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on string and bool");
}

VariantValue* String::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on string and number");
}

VariantValue* String::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on string and list");
}

VariantValue* String::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on string and other value");
}

VariantValue* String::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on string and string");
}

VariantValue* String::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on string and bool");
}

VariantValue* String::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on string and number");
}

VariantValue* String::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on string and list");
}

VariantValue* String::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on string and other value");
}

VariantValue* String::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on string and string");
}

VariantValue* String::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on string and bool");
}

VariantValue* String::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on string and number");
}

VariantValue* String::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on string and list");
}

VariantValue* String::operator&&(VariantValue* other_value) {
    throw std::runtime_error("invalid operation and on string and other value");
}

VariantValue* String::operator&&(String* other_value) {
    throw std::runtime_error("invalid operation and on string and string");
}

VariantValue* String::operator&&(Bool* other_value) {
    throw std::runtime_error("invalid operation and on string and bool");
}

VariantValue* String::operator&&(Number* other_value) {
    throw std::runtime_error("invalid operation and on string and number");
}

VariantValue* String::operator&&(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation and on string and list");
}

VariantValue* String::operator||(VariantValue* other_value) {
    throw std::runtime_error("invalid operation or on string and other value");
}

VariantValue* String::operator||(String* other_value) {
    throw std::runtime_error("invalid operation or on string and string");
}

VariantValue* String::operator||(Bool* other_value) {
    throw std::runtime_error("invalid operation or on string and bool");
}

VariantValue* String::operator||(Number* other_value) {
    throw std::runtime_error("invalid operation or on string and number");
}

VariantValue* String::operator||(ListOfVariantValues* other_value) {
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

std::vector<VariantValue *> String::to_list() {
    throw std::runtime_error("string has no list value");
}

void String::set_value(bool value_) {
    throw std::runtime_error("string has no bool value");
}

void String::set_value(int value_) {
    throw std::runtime_error("string has no int value");
}

void String::set_value(std::vector<VariantValue *> value_) {
    throw std::runtime_error("string has no list value");
}

void String::set_value(std::string value_) {
    value = value_;
}

void String::set_value(VariantValue *value_) {
    value = value_->to_string();
}

bool String::operator==(VariantValue* other_value) {
    return *other_value == this;
}

bool String::operator==(String* other_value) {
    return to_string() == other_value->to_string();
}
bool String::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

bool String::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

bool String::operator!=(String* other_value) {
    return to_string() != other_value->to_string();
}

bool String::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

bool String::operator<(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

bool String::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

bool String::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

bool String::operator<=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

bool String::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

bool String::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

bool String::operator>(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

bool String::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

bool String::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}

bool String::operator>=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on string and other value");
}

bool String::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on string and string");
}

bool String::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on string and bool");
}

bool String::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on string and number");
}

bool String::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on string and listofvariantvalues");
}
