#include "Number.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Number::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

std::unique_ptr<VariantValue> Number::operator+(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value + this;
    return result;
}

std::unique_ptr<VariantValue> Number::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on number and string");
}

std::unique_ptr<VariantValue> Number::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on number and bool");
}

std::unique_ptr<VariantValue> Number::operator+(Number* other_value) {
    return std::make_unique<Number>(to_number() + other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on number and list");
}

std::unique_ptr<VariantValue> Number::operator-(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value - this;
    return result;
}

std::unique_ptr<VariantValue> Number::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on number and string");
}

std::unique_ptr<VariantValue> Number::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on number and bool");
}

std::unique_ptr<VariantValue> Number::operator-(Number* other_value) {
    return std::make_unique<Number>(to_number() - other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on number and list");
}

std::unique_ptr<VariantValue> Number::operator/(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value / this;
    return result;
}

std::unique_ptr<VariantValue> Number::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on number and string");
}

std::unique_ptr<VariantValue> Number::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on number and bool");
}

std::unique_ptr<VariantValue> Number::operator/(Number* other_value) {
    return std::make_unique<Number>(to_number() / other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on number and list");

}

std::unique_ptr<VariantValue> Number::operator*(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value * this;
    return result;
}

std::unique_ptr<VariantValue> Number::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on number and string");

}

std::unique_ptr<VariantValue> Number::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on number and bool");
}

std::unique_ptr<VariantValue> Number::operator*(Number* other_value) {
    return std::make_unique<Number>(to_number() * other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on number and list");
}

std::unique_ptr<VariantValue> Number::operator&&(const std::unique_ptr<VariantValue> & other_value) {
    throw std::runtime_error("invalid operation and on number and other value");
}

std::unique_ptr<VariantValue> Number::operator&&(String* other_value){
    throw std::runtime_error("invalid operation and on number and string");
}

std::unique_ptr<VariantValue> Number::operator&&(Bool* other_value){
    throw std::runtime_error("invalid operation and on number and bool");
}

std::unique_ptr<VariantValue> Number::operator&&(Number* other_value){
    throw std::runtime_error("invalid operation and on number and number");
}

std::unique_ptr<VariantValue> Number::operator&&(ListOfVariantValues* other_value){
    throw std::runtime_error("invalid operation and on number and list");
}

std::unique_ptr<VariantValue> Number::operator||(VariantValue* other_value){
    throw std::runtime_error("invalid operation or on number and other_value");
}

std::unique_ptr<VariantValue> Number::operator||(String* other_value){
    throw std::runtime_error("invalid operation or on number and string");
}

std::unique_ptr<VariantValue> Number::operator||(Bool* other_value){
    throw std::runtime_error("invalid operation or on number and bool");
}

std::unique_ptr<VariantValue> Number::operator||(Number* other_value){
    throw std::runtime_error("invalid operation or on number and number");
}

std::unique_ptr<VariantValue> Number::operator||(ListOfVariantValues* other_value){
    throw std::runtime_error("invalid operation or on number and list");
}

bool Number::to_bool() {
    throw std::runtime_error("number has no bool value");
}

std::string Number::to_string() {
    return std::string( std::to_string(value) );
}

int Number::to_number() {
    return value;
}

std::vector<std::shared_ptr<VariantValue>> Number::to_list() {
    throw std::runtime_error("number has no list value");
}

void Number::set_value(bool value_) {
    throw std::runtime_error("number has no bool value");
}

void Number::set_value(int value_) {
    value = value_;
}

void Number::set_value(std::vector<std::shared_ptr<VariantValue>> value_) {
    throw std::runtime_error("number has no list value");
}

void Number::set_value(std::string value_) {
    throw std::runtime_error("number has no string value");
}

void Number::set_value(VariantValue *value_) {
    value = value_->to_number();
}

std::unique_ptr<VariantValue> Number::operator==(VariantValue* other_value) {
    return *other_value == this;
}

std::unique_ptr<VariantValue> Number::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator==(Number* other_value) {
    return std::make_unique<Bool>(to_number() == other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

std::unique_ptr<VariantValue> Number::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

std::unique_ptr<VariantValue> Number::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator!=(Number* other_value) {
    return std::make_unique<Bool>(to_number() != other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

std::unique_ptr<VariantValue> Number::operator<(VariantValue* other_value) {
    return *other_value < this;
}

std::unique_ptr<VariantValue> Number::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator<(Number* other_value) {
    return std::make_unique<Bool>(to_number() < other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

std::unique_ptr<VariantValue> Number::operator<=(VariantValue* other_value) {
    return *other_value <= this;
}

std::unique_ptr<VariantValue> Number::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator<=(Number* other_value) {
    return std::make_unique<Bool>(to_number() <= other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

std::unique_ptr<VariantValue> Number::operator>(VariantValue* other_value) {
    return *other_value > this;
}

std::unique_ptr<VariantValue> Number::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator>(Number* other_value) {
    return std::make_unique<Bool>(to_number() > other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

std::unique_ptr<VariantValue> Number::operator>=(VariantValue* other_value) {
    return *other_value >= this;
}

std::unique_ptr<VariantValue> Number::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

std::unique_ptr<VariantValue> Number::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

std::unique_ptr<VariantValue> Number::operator>=(Number* other_value) {
    return std::make_unique<Bool>(to_number() >= other_value->to_number());
}

std::unique_ptr<VariantValue> Number::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}
