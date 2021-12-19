#include "Bool.h"
#include "../../../Interpreter/Interpreter.h"
#include <system_error>

void Bool::be_evaluated(Interpreter* interpreter) {
    interpreter->evaluate(this);
}

VariantValue* Bool::operator+(VariantValue* other_value) {
    throw std::runtime_error("invalid operation addition on bool and other value");
}

VariantValue* Bool::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on bool and string");
}

VariantValue* Bool::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on bool and bool");
}

VariantValue* Bool::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on bool and number");
}

VariantValue* Bool::operator+(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation addition on bool and list");
}

VariantValue* Bool::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and other value");
}

VariantValue* Bool::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and string");
}

VariantValue* Bool::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and bool");
}

VariantValue* Bool::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and number");
}

VariantValue* Bool::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on bool and list");
}

VariantValue* Bool::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on bool and other value");
}

VariantValue* Bool::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on bool and string");
}

VariantValue* Bool::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on bool and bool");
}

VariantValue* Bool::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on bool and number");
}

VariantValue* Bool::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on bool and list");
}

VariantValue* Bool::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and other value");
}

VariantValue* Bool::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and string");
}

VariantValue* Bool::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and bool");
}

VariantValue* Bool::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and number");
}

VariantValue* Bool::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on bool and list");
}

VariantValue* Bool::operator&&(VariantValue* other_value) {
    VariantValue* result =* other_value && this;
    return result;
}

VariantValue* Bool::operator&&(String* other_value) {
    if( value && !other_value->to_string().empty() )
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator&&(Bool* other_value) {
    if( value && other_value->to_bool() )
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator&&(Number* other_value) {
    if( value && (other_value->to_number() > 0))
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator&&(ListOfVariantValues* other_value) {
    if( value && !other_value->to_list().empty())
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator||(VariantValue* other_value) {
    VariantValue* result =* other_value || this;
    return result;
}

VariantValue* Bool::operator||(String* other_value) {
    if( value || !other_value->to_string().empty() )
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator||(Bool* other_value) {
    if( value || other_value->to_bool() )
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator||(Number* other_value) {
    if( value || (other_value->to_number() > 0))
        return new Bool(true);
    return new Bool(false);
}

VariantValue* Bool::operator||(ListOfVariantValues* other_value) {
    if( value || !other_value->to_list().empty())
        return new Bool(true);
    return new Bool(false);
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

std::vector<VariantValue *> Bool::to_list() {
    throw std::runtime_error("bool has no list value");
}

void Bool::set_value(bool value_) {
    value = value_;
}

void Bool::set_value(int value_) {
    throw std::runtime_error("bool has no int value");
}

void Bool::set_value(std::vector<VariantValue *> value_) {
    throw std::runtime_error("bool has no list value");
}

void Bool::set_value(std::string value_) {
    throw std::runtime_error("bool has no string value");
}

void Bool::set_value(VariantValue *value_) {
    value = value_->to_bool();
}

bool Bool::operator==(VariantValue* other_value) {
    return *other_value == this;
}

bool Bool::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator==(Bool* other_value) {
    return value == other_value->to_bool();
}

bool Bool::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator==(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

bool Bool::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

bool Bool::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator!=(Bool* other_value) {
    return value != other_value->to_bool();
}

bool Bool::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

bool Bool::operator<(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

bool Bool::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

bool Bool::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

bool Bool::operator<=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and pther value");
}

bool Bool::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

bool Bool::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

bool Bool::operator>(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

bool Bool::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

bool Bool::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}

bool Bool::operator>=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and other value");
}

bool Bool::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and string");
}

bool Bool::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and bool");
}

bool Bool::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and number");
}

bool Bool::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on bool and listofvariantvalues");
}
