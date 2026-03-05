#ifndef MINISCRIPT_TOKEN_H
#define MINISCRIPT_TOKEN_H

#include "miniscript/Word.h"

namespace miniscript {

    struct Token final {
        Word word;
        std::string value;
        int line;
        int column;
    };

    std::ostream& operator<<(std::ostream& os, const Token& token);

}

#endif //MINISCRIPT_TOKEN_H