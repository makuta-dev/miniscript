#ifndef MINISCRIPT_LEXER_H
#define MINISCRIPT_LEXER_H

#include <string_view>
#include <vector>

#include "Token.h"
#include "Trie.h"

namespace miniscript {

    class Lexer final {
    public:
        explicit Lexer(std::string_view input);

        std::vector<Token> tokenize();

    private:
        Token next_token();

        [[nodiscard]] bool is_at_end() const;
        [[nodiscard]] char peek() const;
        [[nodiscard]] char peek_next() const;

        void skip_whitespace_and_comments();
        void consume(size_t n);
        void advance();

        std::string_view m_input;
        std::size_t m_index = 0;
        Trie m_trie;
        int m_line = 1;
        int m_column = 1;
    };

}

#endif //MINISCRIPT_LEXER_H