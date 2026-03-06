#ifndef MINISCRIPT_PARSER_H
#define MINISCRIPT_PARSER_H

#include <vector>

#include "ASTree.h"
#include "miniscript/Token.h"

namespace miniscript {

    class Parser final {
    public:
        explicit Parser(const std::vector<Token>&);
        NodePtr parse();

        static std::runtime_error error(Token token, std::string_view message);

    private:
        [[nodiscard]] Token peek() const;
        [[nodiscard]] Token previous() const;
        [[nodiscard]] bool isEnd() const;
        [[nodiscard]] bool check(Word type) const;

        Token advance();
        bool match(Word type);
        Token consume(Word type, std::string_view message);

        NodePtr parseStatement();
        NodePtr parseIf();
        NodePtr parseFor();
        NodePtr parseWhile();
        NodePtr parseFunction();
        NodePtr parseVariable();
        NodePtr parseBlock();

        NodePtr parseExpression(int = 0);
        NodePtr parseCall(NodePtr callee);
        NodePtr parseIndex(NodePtr container);
        NodePtr parsePrimary();
        NodePtr parseUnary();
        NodePtr parseDict();
        NodePtr parseArray();

        std::vector<Token> m_tokens;
        std::size_t m_current = 0;
    };

}

#endif //MINISCRIPT_PARSER_H