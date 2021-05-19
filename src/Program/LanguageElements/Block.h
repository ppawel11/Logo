#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <utility>
#include <vector>
#include "LanguageElement.h"

class Block {
    std::vector<LanguageElement*> statements;

public:
    explicit Block( std::vector<LanguageElement*> statements_ ): statements{std::move( statements_ )} {}
};


#endif //TKOM_BLOCK_H
