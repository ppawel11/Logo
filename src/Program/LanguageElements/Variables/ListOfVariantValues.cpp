#include "ListOfVariantValues.h"
#include "../../../Interpreter/Interpreter.h"

void ListOfVariantValues::be_evaluated(Interpreter *interpreter) {
    interpreter->evaluate(this);
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator+(VariantValue* other_value) {
    std::unique_ptr<VariantValue> result = *other_value + this;
    return result;
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator+(String* other_value) {
    throw std::runtime_error("invalid operation addition on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator+(Bool* other_value) {
    throw std::runtime_error("invalid operation addition on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator+(Number* other_value) {
    throw std::runtime_error("invalid operation addition on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator+(ListOfVariantValues* other_value) {
    std::vector<std::shared_ptr<VariantValue>> new_elements = other_value->to_list();
    std::copy(elements.begin(), elements.end(), std::back_inserter(new_elements));
    return std::make_unique<ListOfVariantValues>(new_elements );
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator-(VariantValue* other_value) {
    throw std::runtime_error("invalid operation subtract on list and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator-(String* other_value) {
    throw std::runtime_error("invalid operation subtract on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator-(Bool* other_value) {
    throw std::runtime_error("invalid operation subtract on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator-(Number* other_value) {
    throw std::runtime_error("invalid operation subtract on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator-(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation subtract on list and list");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator*(VariantValue* other_value) {
    throw std::runtime_error("invalid operation multiply on list and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator*(String* other_value) {
    throw std::runtime_error("invalid operation multiply on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator*(Bool* other_value) {
    throw std::runtime_error("invalid operation multiply on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator*(Number* other_value) {
    throw std::runtime_error("invalid operation multiply on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator*(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation multiply on list and list");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator/(VariantValue* other_value) {
    throw std::runtime_error("invalid operation divide on list and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator/(String* other_value) {
    throw std::runtime_error("invalid operation divide on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator/(Bool* other_value) {
    throw std::runtime_error("invalid operation divide on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator/(Number* other_value) {
    throw std::runtime_error("invalid operation divide on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator/(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation divide on list and list");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator&&(const std::unique_ptr<VariantValue> & other_value) {
    throw std::runtime_error("invalid operation and on list and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator&&(String* other_value) {
    throw std::runtime_error("invalid operation and on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator&&(Bool* other_value) {
    throw std::runtime_error("invalid operation and on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator&&(Number* other_value) {
    throw std::runtime_error("invalid operation and on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator&&(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation and on list and list");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator||(VariantValue* other_value) {
    throw std::runtime_error("invalid operation or on list and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator||(String* other_value) {
    throw std::runtime_error("invalid operation or on list and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator||(Bool* other_value) {
    throw std::runtime_error("invalid operation or on list and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator||(Number* other_value) {
    throw std::runtime_error("invalid operation or on list and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator||(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation or on list and list");
}

bool ListOfVariantValues::to_bool() {
    throw std::runtime_error("list has no bool value");
}

std::string ListOfVariantValues::to_string() {
    std::string printed_list = "[";
    for( auto& elem : elements )
    {
        printed_list += elem->to_string() + ", ";
    }
    printed_list += "]";
    return printed_list;
}

int ListOfVariantValues::to_number() {
    throw std::runtime_error("list has no numeric value");
}

std::vector<std::shared_ptr<VariantValue>> ListOfVariantValues::to_list() {
    return elements;
}

void ListOfVariantValues::set_value(bool value_) {
    throw std::runtime_error("list has no bool value");
}

void ListOfVariantValues::set_value(int value_) {
    throw std::runtime_error("list has no int value");
}

void ListOfVariantValues::set_value(std::vector<std::shared_ptr<VariantValue>> value_) {
    elements = value_;
}

void ListOfVariantValues::set_value(std::string value_) {
    throw std::runtime_error("list has no string value");
}

void ListOfVariantValues::set_value(VariantValue *value_) {
    elements = value_->to_list();
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator==(VariantValue* other_value) {
    return *other_value == this;
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator==(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator==(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator==(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator==(ListOfVariantValues* other_value) {
    if( elements.size() != other_value->to_list().size())
        return std::make_unique<Bool>(false);

    for( int i = 0; i < elements.size(); ++i )
    {
        if( *elements[i] != other_value->to_list()[i].get() )
            return std::make_unique<Bool>(false);
    }
    return std::make_unique<Bool>(true);
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator!=(VariantValue* other_value) {
    return *other_value != this;
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator!=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator!=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator!=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator!=(ListOfVariantValues* other_value) {
    return std::make_unique<Bool>( !( *this == other_value ) );
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator<=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>=(VariantValue* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and other value");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>=(String* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and string");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>=(Bool* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and bool");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>=(Number* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and number");
}

std::unique_ptr<VariantValue> ListOfVariantValues::operator>=(ListOfVariantValues* other_value) {
    throw std::runtime_error("invalid operation comparison on listofvariantvalues and listofvariantvalues");
}
