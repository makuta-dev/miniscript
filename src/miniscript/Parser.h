#ifndef MINISCRIPT_PARSER_H
#define MINISCRIPT_PARSER_H

#include "miniscript/ASTree.h"
#include "miniscript/Token.h"

namespace ms {

    class Parser final {
    public:
        explicit Parser(const std::vector<Token>&);
        NodePtr parse();

    private:
        std::vector<Token> m_tokens;
        std::size_t m_index;
    };

}

#endif //MINISCRIPT_PARSER_H