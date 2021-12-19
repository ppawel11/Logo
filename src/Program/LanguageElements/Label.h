#ifndef TKOM_LABEL_H
#define TKOM_LABEL_H

#include "Variables/Assignable.h"
#include <string>

class Label: public Assignable {
    std::string variable_name;

public:
    Label( std::string variable_name_ ): variable_name{variable_name_ }, Assignable() {}

    std::string get_variable_name();
    void be_evaluated(Interpreter *interpreter) override;
};


#endif //TKOM_LABEL_H
