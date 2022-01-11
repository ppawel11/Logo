#ifndef TKOM_STRING_H
#define TKOM_STRING_H

#include "Assignable.h"
#include "VariantValue.h"

#include <string>
#include <utility>

class String: public Assignable {
    std::string value;
public:
    String(): value{""} {};
    explicit String( std::string value_ ): value{std::move(value_)}, Assignable() {}
    ~String() = default;
    void be_evaluated(Interpreter *interpreter) override;

    const std::string &getValue() const;

    void setValue(const std::string &value);
};

#endif //TKOM_STRING_H

