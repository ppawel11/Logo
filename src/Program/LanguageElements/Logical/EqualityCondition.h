#ifndef TKOM_EQUALITYCONDITION_H
#define TKOM_EQUALITYCONDITION_H

#include <utility>
#include "RelationalCondition.h"
#include <optional>

class EqualityCondition: public Assignable {
    // relational_condition, [ equality_operator, relational_condition ]
    Assignable * first_condition;
    std::optional<Assignable*> second_condition;
    std::optional<bool> equals;
public:
    explicit EqualityCondition( Assignable * first_condition_ ) :
        first_condition{ first_condition_ }
    {}

    EqualityCondition( Assignable* first_condition_, bool equals_, Assignable* second_condition_ ) :
        first_condition{ first_condition_ },
        equals{ equals_ },
        second_condition{ second_condition_ }
    {}

    Assignable *getFirstCondition() const;

    const std::optional<Assignable *> &getSecondCondition() const;

    const std::optional<bool> &getEquals() const;

    void be_evaluated(Interpreter *interpreter) override;
};


#endif //TKOM_EQUALITYCONDITION_H
