#ifndef TKOM_BOOL_H
#define TKOM_BOOL_H


#include "Assignable.h"
#include "VariantValue.h"

class Bool: public Assignable {
    bool value;
public:
    Bool(): value{ false } {};
    explicit Bool(bool value_): value{value_}, Assignable() {}
    ~Bool() = default;
    void be_evaluated(Evaluator *interpreter) override;

    bool isValue() const;

    void setValue(bool value);
};


#endif //TKOM_BOOL_H
