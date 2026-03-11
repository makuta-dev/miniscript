#ifndef MINISCRIPT_LEXER_H
#define MINISCRIPT_LEXER_H

#include <string_view>
#include <vector>

#include "miniscript/Token.h"

namespace ms {

    class Lexer final {
    public:
        explicit Lexer(std::string_view);
        bool nextToken(Token&);

    private:
        [[nodiscard]] bool isAtEnd() const;
        [[nodiscard]] char peek() const;

        char advance();
        bool match(char expected);
        void skipWhitespace();

        Token lexIdentifier();
        Token lexOperator();
        Token lexNumber();
        Token lexString();

        Token new_token(Word word, const char * str = "") const;

        std::string_view m_input;
        std::size_t m_index{0};
        std::size_t start{0};
        int line{1};
        int column{1};
    };

}

#endif //MINISCRIPT_LEXER_H