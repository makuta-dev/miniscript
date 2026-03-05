#include "miniscript/Lexer.h"

namespace miniscript {

    const std::unordered_map<std::string_view, Word> RESERVED = {
        {"func",    Word::Func},
        {"let",     Word::Let},
        {"ret",     Word::Ret},
        {"if",      Word::If},
        {"else",    Word::Else},
        {"while",   Word::While},
        {"for",     Word::For},
        {"break",   Word::Break},
        {"continue",Word::Continue},
        {"import",  Word::Import},
        {"true",    Word::True},
        {"false",   Word::False},
        {"null",    Word::Null},
    };

    Lexer::Lexer(const std::string_view input) : m_input(input) {}

    std::vector<Token> Lexer::tokenize() {
        auto tokens = std::vector<Token>();
        while (!is_at_end()) {
            skip_whitespace_and_comments();
            if (is_at_end()) break;

            tokens.push_back(next_token());
        }
        tokens.emplace_back(Word::EndOfFile,"", m_line, m_column);
        return tokens;
    }

    Token Lexer::next_token() {
        const int start_line = m_line;
        const int start_col = m_column;

        if (const auto [op_word, op_len] = m_trie.find_longest(m_input.substr(m_index)); op_word != Word::UNKNOWN) {
            const std::string_view val = m_input.substr(m_index, op_len);
            consume(op_len);
            return {op_word, std::string(val), start_line, start_col};
        }

        const char c = peek();

        // Identifiers & Keywords
        if (std::isalpha(c) || c == '_') {
            const size_t start = m_index;
            while (std::isalnum(peek()) || peek() == '_') advance();
            const std::string_view text = m_input.substr(start, m_index - start);
            const Word type = RESERVED.contains(text) ? RESERVED.at(text) : Word::Identifier;
            return {type, std::string(text), start_line, start_col};
        }

        // Numbers
        if (std::isdigit(c)) {
            const size_t start = m_index;
            while (std::isdigit(peek())) advance();
            // Simple float support
            if (peek() == '.' && std::isdigit(peek_next())) {
                advance();
                while (std::isdigit(peek())) advance();
            }
            return {Word::Number, std::string(m_input.substr(start, m_index - start)), start_line, start_col};
        }

        // Strings
        if (c == '"') {
            advance(); // opening "
            const size_t start = m_index;
            while (peek() != '"' && !is_at_end()) {
                 advance();
            }
            const std::string_view val = m_input.substr(start, m_index - start);
            if (peek() == '"') advance(); // closing "
            return {Word::String, std::string(val), start_line, start_col};
        }

        advance();
        return {Word::UNKNOWN, std::string(1, c), start_line, start_col};
    }

    bool Lexer::is_at_end() const { return m_index >= m_input.size(); }
    char Lexer::peek() const { return is_at_end() ? '\0' : m_input[m_index]; }
    char Lexer::peek_next() const { return m_index + 1 >= m_input.size() ? '\0' : m_input[m_index + 1]; }

    void Lexer::advance() {
        if (m_input[m_index] == '\n') { m_line++; m_column = 1; }
        else m_column++;
        m_index++;
    }

    void Lexer::consume(const size_t n) {
        for (size_t i = 0; i < n; ++i) advance();
    }

    void Lexer::skip_whitespace_and_comments() {
        while (!is_at_end()) {
            if (const char c = peek(); std::isspace(c)) advance();
            else if (c == '/' && peek_next() == '/') {
                while (peek() != '\n' && !is_at_end()) advance();
            } else break;
        }
    }

}