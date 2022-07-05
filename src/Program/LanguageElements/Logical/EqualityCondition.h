#ifndef TKOM_EQUALITYCONDITION_H
#define TKOM_EQUALITYCONDITION_H

#include "../Variables/Assignable.h"
#include <utility>
#include <optional>
#include <memory>

class EqualityCondition: public Assignable {
    // relational_condition, [ equality_operator, relational_condition ]
    std::unique_ptr<Assignable> first_condition;
    std::optional<std::unique_ptr<Assignable>> second_condition;
    std::optional<bool> equals;
public:
    explicit EqualityCondition( std::unique_ptr<Assignable> first_condition_ ) :
        first_condition{ std::move(first_condition_) }
    {}

    EqualityCondition( std::unique_ptr<Assignable> first_condition_, bool equals_, std::unique_ptr<Assignable> second_condition_ ) :
        first_condition{ std::move(first_condition_) },
        equals{ equals_ },
        second_condition{ std::move(second_condition_) }
    {}

    const std::unique_ptr<Assignable> & getFirstCondition() const;

    const std::optional<std::unique_ptr<Assignable>> & getSecondCondition() const;

    const std::optional<bool> &getEquals() const;

    void be_evaluated(Evaluator *interpreter) override;
};


#endif //TKOM_EQUALITYCONDITION_H
