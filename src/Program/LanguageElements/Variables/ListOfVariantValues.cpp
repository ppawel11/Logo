#include "ListOfVariantValues.h"
#include "../../../Interpreter/Interpreter.h"

void ListOfVariantValues::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

VariantValue* ListOfVariantValues::operator+(VariantValue* other_value) {
    VariantValue* result = *other_value + this;
    return result;
}

VariantValue* ListOfVariantValues::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on list and string");
}

VariantValue* ListOfVariantValues::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on list and bool");
}

VariantValue* ListOfVariantValues::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on list and number");
}

VariantValue* ListOfVariantValues::operator+(ListOfVariantValues* other_value) {
    std::vector<VariantValue*> new_elements = other_value->to_list();
    std::copy(elements.begin(), elements.end(), std::back_inserter(new_elements));
    return new ListOfVariantValues(new_elements );
}

VariantValue* ListOfVariantValues::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on list and other value");
}

VariantValue* ListOfVariantValues::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on list and string");
}

VariantValue* ListOfVariantValues::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on list and bool");
}

VariantValue* ListOfVariantValues::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on list and number");
}

VariantValue* ListOfVariantValues::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on list and list");
}

VariantValue* ListOfVariantValues::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on list and other value");
}

VariantValue* ListOfVariantValues::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on list and string");
}

VariantValue* ListOfVariantValues::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on list and bool");
}

VariantValue* ListOfVariantValues::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on list and number");
}

VariantValue* ListOfVariantValues::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on list and list");
}

VariantValue* ListOfVariantValues::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on list and other value");
}

VariantValue* ListOfVariantValues::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on list and string");
}

VariantValue* ListOfVariantValues::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on list and bool");
}

VariantValue* ListOfVariantValues::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on list and number");
}

VariantValue* ListOfVariantValues::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on list and list");
}

VariantValue* ListOfVariantValues::operator&&(VariantValue* other_value) {
    throw std::runtime_error("invalid operation and on list and other value");
}

VariantValue* ListOfVariantValues::operator&&(String* other_value) {
    throw std::runtime_error("invalid operation and on list and string");
}

VariantValue* ListOfVariantValues::operator&&(Bool* other_value) {
    throw std::runtime_error("invalid operation and on list and bool");
}

VariantValue* ListOfVariantValues::operator&&(Number* other_value) {
    throw std::runtime_error("invalid operation and on list and number");
}

VariantValue* ListOfVariantValues::operator&&(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation and on list and list");
}

VariantValue* ListOfVariantValues::operator||(VariantValue* other_value) {
    throw std::runtime_error("invalid operation or on list and other value");
}

VariantValue* ListOfVariantValues::operator||(String* other_value) {
    throw std::runtime_error("invalid operation or on list and string");
}

VariantValue* ListOfVariantValues::operator||(Bool* other_value) {
    throw std::runtime_error("invalid operation or on list and bool");
}

VariantValue* ListOfVariantValues::operator||(Number* other_value) {
    throw std::runtime_error("invalid operation or on list and number");
}

VariantValue* ListOfVariantValues::operator||(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation or on list and list");
}

bool ListOfVariantValues::to_bool() {
    throw std::runtime_error("list has no bool value");
}

std::string ListOfVariantValues::to_string() {
    std::string printed_list = "[";
    for( auto elem : elements )
    {
        printed_list += elem->to_string() + ", ";
    }
    printed_list += "]";
    return printed_list;
}

int ListOfVariantValues::to_number() {
    throw std::runtime_error("list has no numeric value");
}

std::vector<VariantValue *> ListOfVariantValues::to_list() {
    return elements;
}

void ListOfVariantValues::set_value(bool value_) {
    throw std::runtime_error("list has no bool value");
}

void ListOfVariantValues::set_value(int value_) {
    throw std::runtime_error("list has no int value");
}

void ListOfVariantValues::set_value(std::vector<VariantValue *> value_) {
    elements = value_;
}

void ListOfVariantValues::set_value(std::string value_) {
    throw std::runtime_error("list has no string value");
}

void ListOfVariantValues::set_value(VariantValue *value_) {
    elements = value_->to_list();
}

bool ListOfVariantValues::operator==(VariantValue* other_value) {
    return *other_value == this;
}

bool ListOfVariantValues::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator==(ListOfVariantValues* other_value) {
    
}

bool ListOfVariantValues::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

bool ListOfVariantValues::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator!=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

bool ListOfVariantValues::operator<(VariantValue* other_value) {
    return *other_value < this;
}

bool ListOfVariantValues::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

bool ListOfVariantValues::operator<=(VariantValue* other_value) {
    return *other_value <= this;
}

bool ListOfVariantValues::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

bool ListOfVariantValues::operator>(VariantValue* other_value) {
    return *other_value > this;
}

bool ListOfVariantValues::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

bool ListOfVariantValues::operator>=(VariantValue* other_value) {
    return *other_value >= this;
}

bool ListOfVariantValues::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

bool ListOfVariantValues::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

bool ListOfVariantValues::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

bool ListOfVariantValues::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}
