#ifndef MINISCRIPT_TOKEN_H
#define MINISCRIPT_TOKEN_H

#include "miniscript/Word.h"

namespace ms {

    struct Token final {
        Word word;
        std::string value;
        int line;
        int column;
    };

    std::string toString(const Token& token);

}

#endif //MINISCRIPT_TOKEN_H