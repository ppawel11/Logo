#ifndef TKOM_RETURN_H
#define TKOM_RETURN_H

#include "LanguageElement.h"
#include "Variables/Assignable.h"
#include "../Program.h"

class Return: public LanguageElement {
    std::unique_ptr<Assignable> value;
public:
    explicit Return( std::unique_ptr<Assignable> value_ ): value{ std::move(value_) }, LanguageElement() {}

    void be_handled(LanguageElementVisitor *interpreter) override;

    const std::unique_ptr<Assignable> & getValue() const;
};


#endif //TKOM_RETURN_H
