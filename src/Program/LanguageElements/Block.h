#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <utility>
#include <vector>
#include <memory>
#include "LanguageElement.h"

class Block: public LanguageElement {
    std::vector<std::unique_ptr<LanguageElement>> statements;

public:
    explicit Block( std::vector<std::unique_ptr<LanguageElement>> statements_ ): statements{std::move( statements_ )} {}

    void be_handled(Interpreter * interpreter) override {
        for( auto const & a : statements )
        {
            a->be_handled(interpreter);
        }
    }

    const std::vector<std::unique_ptr<LanguageElement>> &getStatements() const {
        return statements;
    }
};

#endif //TKOM_BLOCK_H
