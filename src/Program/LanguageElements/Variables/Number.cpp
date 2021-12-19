#include "Number.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Number::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

VariantValue* Number::operator+(VariantValue* other_value) {
    VariantValue* result = *other_value + this;
    return result;
}

VariantValue* Number::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on number and string");
}

VariantValue* Number::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on number and bool");
}

VariantValue* Number::operator+(Number* other_value) {
    return new Number(to_number() + other_value->to_number());
}

VariantValue* Number::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on number and list");
}

VariantValue* Number::operator-(VariantValue* other_value) {
    VariantValue* result = *other_value - this;
    return result;
}

VariantValue* Number::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on number and string");
}

VariantValue* Number::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on number and bool");
}

VariantValue* Number::operator-(Number* other_value) {
    return new Number(to_number() - other_value->to_number());
}

VariantValue* Number::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on number and list");
}

VariantValue* Number::operator/(VariantValue* other_value) {
    VariantValue* result = *other_value / this;
    return result;
}

VariantValue* Number::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on number and string");
}

VariantValue* Number::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on number and bool");
}

VariantValue* Number::operator/(Number* other_value) {
    return new Number(to_number() / other_value->to_number());
}

VariantValue* Number::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on number and list");

}

VariantValue* Number::operator*(VariantValue* other_value) {
    VariantValue* result = *other_value * this;
    return result;
}

VariantValue* Number::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on number and string");

}

VariantValue* Number::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on number and bool");
}

VariantValue* Number::operator*(Number* other_value) {
    return new Number(to_number() * other_value->to_number());
}

VariantValue* Number::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on number and list");
}

VariantValue* Number::operator&&(VariantValue* other_value) {
    throw std::runtime_error("invalid operation and on number and other value");
}

VariantValue* Number::operator&&(String* other_value){
    throw std::runtime_error("invalid operation and on number and string");
}

VariantValue* Number::operator&&(Bool* other_value){
    throw std::runtime_error("invalid operation and on number and bool");
}

VariantValue* Number::operator&&(Number* other_value){
    throw std::runtime_error("invalid operation and on number and number");
}

VariantValue* Number::operator&&(ListOfVariantValues* other_value){
    throw std::runtime_error("invalid operation and on number and list");
}

VariantValue* Number::operator||(VariantValue* other_value){
    throw std::runtime_error("invalid operation or on number and other_value");
}

VariantValue* Number::operator||(String* other_value){
    throw std::runtime_error("invalid operation or on number and string");
}

VariantValue* Number::operator||(Bool* other_value){
    throw std::runtime_error("invalid operation or on number and bool");
}

VariantValue* Number::operator||(Number* other_value){
    throw std::runtime_error("invalid operation or on number and number");
}

VariantValue* Number::operator||(ListOfVariantValues* other_value){
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

std::vector<VariantValue *> Number::to_list() {
    throw std::runtime_error("number has no list value");
}

void Number::set_value(bool value_) {
    throw std::runtime_error("number has no bool value");
}

void Number::set_value(int value_) {
    value = value_;
}

void Number::set_value(std::vector<VariantValue *> value_) {
    throw std::runtime_error("number has no list value");
}

void Number::set_value(std::string value_) {
    throw std::runtime_error("number has no string value");
}

void Number::set_value(VariantValue *value_) {
    value = value_->to_number();
}

bool Number::operator==(VariantValue* other_value) {
    return *other_value == this;
}

bool Number::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator==(Number* other_value) {
    return to_number() == other_value->to_number();
}

bool Number::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

bool Number::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

bool Number::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator!=(Number* other_value) {
    return to_number() != other_value->to_number();
}

bool Number::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

bool Number::operator<(VariantValue* other_value) {
    return *other_value < this;
}

bool Number::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator<(Number* other_value) {
    return to_number() < other_value->to_number();
}

bool Number::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

bool Number::operator<=(VariantValue* other_value) {
    return *other_value <= this;
}

bool Number::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator<=(Number* other_value) {
    return to_number() <= other_value->to_number();
}

bool Number::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

bool Number::operator>(VariantValue* other_value) {
    return *other_value > this;
}

bool Number::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator>(Number* other_value) {
    return to_number() > other_value->to_number();
}

bool Number::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}

bool Number::operator>=(VariantValue* other_value) {
    return *other_value >= this;
}

bool Number::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on number and string");
}

bool Number::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on number and bool");
}

bool Number::operator>=(Number* other_value) {
    return to_number() >= other_value->to_number();
}

bool Number::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on number and listofvariantvalues");
}
