#include "Lexer.h"

#include <unordered_map>

namespace ms {

    Lexer::Lexer(const std::string_view input, const int line) : m_input(input), m_line(line) {}

    bool Lexer::nextToken(Token& t) {
        skipWhitespace();
        m_start = m_index;

        if (isAtEnd()) {
            t = { Word::EndOfFile, "", m_line, m_column };
            return false;
        }

        const char c = peek();

        if (std::isalpha(c) || c == '_') {
            t = lexIdentifier();
            return true;
        }

        if (std::isdigit(c)) {
            t = lexNumber();
            return true;
        }

        if (c == '"') {
            t = lexString();
            return true;
        }

        t = lexOperator();
        return true;
    }

    std::vector<Token> Lexer::getTokens() {
        std::vector<Token> tokens;
        Token token;
        while (nextToken(token)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool Lexer::isAtEnd() const {
        return m_index >= m_input.size();
    }

    char Lexer::peek() const {
        return isAtEnd() ? '\0' : m_input[m_index];
    }

    char Lexer::advance() {
        m_column++;
        return m_input[m_index++];
    }

    bool Lexer::match(const char expected) {
        if (isAtEnd()) return false;

        if (m_input[m_index] == expected) {
            m_index++;
            return true;
        }
        return false;
    }

    void Lexer::skipWhitespace() {
        for (;;) {
            switch (peek()) {
                case ' ': case '\r': case '\t': advance(); break;
                case '\n': m_line++; m_column = 1; advance(); break;
                case '/':
                    if (m_input[m_index+1] == '/') {
                        while (peek() != '\n' && !isAtEnd()) advance();
                    } else return;
                    break;
                default: return;
            }
        }
    }

    Token Lexer::lexIdentifier() {
        while (std::isalnum(peek()) || peek() == '_') advance();

        std::string_view text = m_input.substr(m_start, m_index - m_start);
        auto type = Word::Identifier;

        static const std::unordered_map<std::string_view, Word> keywords = {
            {"let",     Word::Let},
            {"const",   Word::Const},
            {"func",    Word::Function},
            {"ret",     Word::Return},
            {"while",   Word::While},
            {"for",     Word::For},
            {"in",      Word::In},
            {"do",      Word::Do},
            {"if",      Word::If},
            {"else",    Word::Else},
            {"match",   Word::Match},
            {"true",    Word::True},
            {"false",   Word::False},
            {"null",    Word::Null}
        };

        if (const auto it = keywords.find(text); it != keywords.end()) {
            type = it->second;
            text = "";
        }

        return {type, text, m_line, m_column};
    }

    Token Lexer::lexOperator() {
        switch (advance()) {
            case '=':
                if (match('=')) return new_token(Word::Equals);
                return new_token(Word::Assign);
            case '+':
                if (match('+')) return new_token(Word::PlusPlus);
                if (match('=')) return new_token(Word::PlusAssign);
                return new_token(Word::Plus);
            case '-':
                if (match('-')) return new_token(Word::MinusMinus);
                if (match('=')) return new_token(Word::MinusAssign);
                return new_token(Word::Minus);
            case '*':
                if (match('=')) return new_token(Word::MultiplyAssign);
                return new_token(Word::Multiply);
            case '/':
                if (match('=')) return new_token(Word::DivideAssign);
                return new_token(Word::Divide);
            case '%':
                if (match('=')) return new_token(Word::ModulusAssign);
                return new_token(Word::Modulus);
            case '^':
                if (match('=')) return new_token(Word::BitXorAssign);
                return new_token(Word::BitXor);
            case '&':
                if (match('&')) return new_token(Word::And);
                if (match('=')) return new_token(Word::BitAndAssign);
                return new_token(Word::BitAnd);
            case '|':
                if (match('|')) return new_token(Word::Or);
                if (match('=')) return new_token(Word::BitOrAssign);
                return new_token(Word::BitOr);
            case '!':
                if (match('=')) return new_token(Word::NotEquals);
                return new_token(Word::Not);
            case '~':
                if (match('=')) return new_token(Word::InvAssign);
                return new_token(Word::Inv);
            case '(':
                return new_token(Word::LeftParen);
            case ')':
                return new_token(Word::RightParen);
            case '{':
                return new_token(Word::LeftBrace);
            case '}':
                return new_token(Word::RightBrace);
            case '[':
                return new_token(Word::LeftBracket);
            case ']':
                return new_token(Word::RightBracket);
            case '.':
                return new_token(Word::Dot);
            case ',':
                return new_token(Word::Comma);
            case ':':
                return new_token(Word::Colon);
            case '<': {
                if (match('<')) {
                    if (match('<')) {
                        return new_token(match('=') ? Word::LeftRotateAssign : Word::LeftRotate);
                    }
                    return new_token(match('=') ? Word::LeftShiftAssign : Word::LeftShift);
                }
                return new_token(match('=') ? Word::LessEquals : Word::Less);
            }
            case '>': {
                if (match('>')) {
                    if (match('>')) {
                        return new_token(match('=') ? Word::RightRotateAssign : Word::RightRotate);
                    }
                    return new_token(match('=') ? Word::RightShiftAssign : Word::RightShift);
                }
                return new_token(match('=') ? Word::GreaterEquals : Word::Greater);
            }
            default:
                return { Word::UNKNOWN, m_input.substr(m_start, 1), m_line, m_column };
        }
    }

    Token Lexer::lexNumber() {
        while (std::isdigit(peek()))
            advance();
        if (peek() == '.') {
            advance();
            while (std::isdigit(peek()))
                advance();
        }

        const std::string_view text = m_input.substr(m_start, m_index - m_start);
        return {Word::Number, text, m_line, m_column};
    }

    Token Lexer::lexString() {
        const int startLine = m_line;
        const int startColumn = m_column;

        advance();
        const std::size_t content_start = m_index;

        bool has_interpolation = false;
        int brace_stack = 0;
        bool inside_inner_quote = false;

        while (!isAtEnd()) {
            if (const char c = peek(); c == '"' && brace_stack > 0) {
                inside_inner_quote = !inside_inner_quote;
                advance();
            } else if (c == '"' && brace_stack == 0 && !inside_inner_quote) {
                break;
            } else if (c == '{' && !inside_inner_quote) {
                brace_stack++;
                has_interpolation = true;
                advance();
            } else if (c == '}' && !inside_inner_quote) {
                if (brace_stack > 0) brace_stack--;
                advance();
            } else {
                if (c == '\n') { m_line++; m_column = 1; }
                advance();
            }
        }

        const std::string_view text = m_input.substr(content_start, m_index - content_start);

        if (!isAtEnd()) advance();

        const Word type = has_interpolation ? Word::StringInterpolation : Word::String;
        return {type, text, startLine, startColumn};
    }

    Token Lexer::new_token(const Word word, const char *str) const {
        return {word, str, m_line, m_column};
    }
}
