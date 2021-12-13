#ifndef TKOM_BOOL_H
#define TKOM_BOOL_H


#include "Assignable.h"

class Bool: public Assignable {
    bool value;
public:
    explicit Bool(bool value_): value{value_}, Assignable() {}

    void be_evaluated(Interpreter *interpreter) override;

    bool get_value() const;

};


#endif //TKOM_BOOL_H
