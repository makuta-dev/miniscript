#include "Parser.h"

namespace ms {

    Parser::Parser(const std::vector<Token>& t) : m_tokens(t), m_index(0) {}

    NodePtr Parser::parse() {
        NodeVec statements;
        return node<ProgramNode>(std::move(statements));
    }

}