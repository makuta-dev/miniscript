#include "Parser.h"

namespace ms {

    Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens), m_index(0) {}

    NodePtr Parser::parse() {
        return node<ProgramNode>();
    }

}