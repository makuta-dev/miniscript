#include "miniscript/Parser.h"

#include <format>

namespace miniscript {

    Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens){}

    NodePtr Parser::parse() {
        auto program_block = node<BlockNode>();
        while (!isEnd()) {
            program_block->statements.push_back(parseStatement());
        }
        return program_block;
    }

    std::runtime_error Parser::error(Token token, std::string_view message) {
        const std::string formatted = std::format(
            "[Line {}:{}] Error at '{}': {}",
            token.line,
            token.column,
            token.value,
            message
        );
        return std::runtime_error(formatted);
    }

    Token Parser::peek() const {
        return m_tokens[m_current];
    }

    Token Parser::previous() const {
        return m_tokens[m_current - 1];
    }

    bool Parser::isEnd() const {
        return peek().word == Word::EndOfFile;
    }

    bool Parser::check(const Word type) const {
        if (isEnd()) return false;
        return peek().word == type;
    }

    Token Parser::advance() {
        if (!isEnd()) m_current++;
        return previous();
    }

    bool Parser::match(const Word type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    Token Parser::consume(const Word type, const std::string_view message) {
        if (check(type)) return advance();
        throw std::runtime_error(std::string(message));
    }

    NodePtr Parser::parseStatement() {
        if (match(Word::Let))       return parseVariable();
        if (match(Word::Func))      return parseFunction();
        if (match(Word::If))        return parseIf();
        if (match(Word::While))     return parseWhile();
        if (match(Word::For))       return parseFor();
        if (match(Word::Break))     return node<BreakNode>();
        if (match(Word::Continue))  return node<ContinueNode>();
        if (match(Word::Ret)) {
            auto n = node<ReturnNode>();
            if (!check(Word::RightBrace)) {
                n->variable = parseExpression(0);
            }
            return n;
        }

        return parseExpression();
    }

    NodePtr Parser::parseBlock() {
        auto block = node<BlockNode>();
        consume(Word::LeftBrace, "Expected '{' before block.");
        while (!check(Word::RightBrace) && !isEnd()) {
            block->statements.push_back(parseStatement());
        }
        consume(Word::RightBrace, "Expected '}' after block.");
        return block;
    }

    NodePtr Parser::parseIf() {
        consume(Word::LeftParen, "Expected '(' after 'if'.");
        NodePtr condition = parseExpression(0);
        consume(Word::RightParen, "Expected ')' after condition.");

        NodePtr thenBranch = parseBlock();
        NodePtr elseBranch = nullptr;

        if (match(Word::Else)) {
            elseBranch = parseBlock();
        }

        auto n = node<IfNode>();
        n->condition = std::move(condition);
        n->thenBody = std::move(thenBranch);
        n->elseBody = std::move(elseBranch);
        return n;
    }

    NodePtr Parser::parseFor() {
        consume(Word::LeftParen, "Expected '(' after 'for'.");
        consume(Word::Let, "Expected 'let' inside for-loop declaration.");
        const Token varToken = consume(Word::Identifier, "Expected iterator variable name.");
        consume(Word::In, "Expected 'in' after variable name.");
        NodePtr collection = parseExpression(0);
        consume(Word::RightParen, "Expected ')' after for-in expression.");
        NodePtr body = parseBlock();

        auto n = node<ForNode>();
        n->iterator_name = varToken.value;
        n->collection = std::move(collection);
        n->body = std::move(body);

        return n;
    }

    NodePtr Parser::parseWhile() {
        consume(Word::LeftParen, "Expected '(' after 'while'.");
        NodePtr condition = parseExpression(0);
        consume(Word::RightParen, "Expected ')' after condition.");

        NodePtr body = parseBlock();

        auto n = node<WhileNode>();
        n->condition = std::move(condition);
        n->body = std::move(body);
        n->is_do_while = false;
        return n;
    }

    NodePtr Parser::parseFunction() {
        const Token nameToken = consume(Word::Identifier, "Expected function name.");
        consume(Word::LeftParen, "Expected '(' after function name.");
        NodeVec parameters;
        if (!check(Word::RightParen)) {
            do {
                const Token param = consume(Word::Identifier, "Expected parameter name.");
                auto argNode = node<ArgumentNode>();
                argNode->name = param.value;
                parameters.push_back(std::move(argNode));
            } while (match(Word::Comma));
        }
        consume(Word::RightParen, "Expected ')' after parameters.");

        auto funcNode = node<FunctionNode>();
        funcNode->name = nameToken.value;
        funcNode->arguments = std::move(parameters);

        if (match(Word::Assign)) {
            auto block = node<BlockNode>();
            auto returnStmt = node<ReturnNode>();

            auto expr = parseExpression();

            returnStmt->variable = std::move(expr);
            block->statements.push_back(std::move(returnStmt));
            funcNode->body = std::move(block);
        } else {
            funcNode->body = parseBlock();
        }

        return funcNode;
    }

    NodePtr Parser::parseVariable() {
        const Token nameToken = consume(Word::Identifier, "Expected variable name after 'let'.");

        NodePtr value = nullptr;

        if (match(Word::Assign)) {
            value = parseExpression();
        } else {
            value = node<LiteralNode>(Token{Word::Null, "null"});
        }

        auto varNode = node<VariableNode>();
        varNode->name = nameToken.value;
        varNode->value = std::move(value);

        return varNode;
    }

    int getPrecedence(const Word op) {
        switch (op) {
            case Word::Assign:
            case Word::PlusAssign:
            case Word::MinusAssign:
            case Word::AsteriskAssign:
            case Word::SlashAssign:
            case Word::PercentAssign:
            case Word::AndAssign:
            case Word::OrAssign:
            case Word::XorAssign:
            case Word::LShiftAssign:
            case Word::RShiftAssign:
            case Word::RotLAssign:
            case Word::RotRAssign:
                return 1;

            case Word::Or: return 2;
            case Word::And: return 3;

            case Word::BitOr:
            case Word::BitXor:
            case Word::BitAnd:
                return 4;

            case Word::Equal:
            case Word::NotEqual:
                return 5;

            case Word::Less:
            case Word::LessEqual:
            case Word::More:
            case Word::MoreEqual:
                return 6;

            case Word::LeftShift:
            case Word::RightShift:
            case Word::RotateLeft:
            case Word::RotateRight:
                return 7;

            case Word::Plus:
            case Word::Minus:
                return 8;

            case Word::Asterisk:
            case Word::Slash:
            case Word::Percent:
                return 9;

            default:
                return 0;
        }
    }

    NodePtr Parser::parseExpression(const int precedence) {
        NodePtr left = parseUnary();

        while (true) {
            if (match(Word::LeftParen)) {
                left = parseCall(std::move(left));
                continue;
            }
            if (match(Word::LeftBracket)) {
                left = parseIndex(std::move(left));
                continue;
            }
            if (match(Word::Dot)) {
                Token property = consume(Word::Identifier, "Expected property name after '.'.");
                auto index = node<IndexNode>();
                index->variable = std::move(left);
                index->index = node<LiteralNode>(property);
                left = std::move(index);
                continue;
            }

            const Token op = peek();
            const int prec = getPrecedence(op.word);
            if (prec <= precedence) break;
            advance();
            const int next_min_prec = prec == 1 ? prec - 1 : prec;
            NodePtr right = parseExpression(next_min_prec);
            auto binary = node<BinaryNode>();
            binary->op = op.word;
            binary->left = std::move(left);
            binary->right = std::move(right);
            left = std::move(binary);
        }

        return left;
    }

    NodePtr Parser::parseCall(NodePtr callee) {
        auto callNode = node<CallNode>();
        callNode->name = std::move(callee);

        if (!check(Word::RightParen)) {
            do {
                callNode->arguments.push_back(parseExpression(0));
            } while (match(Word::Comma));
        }

        consume(Word::RightParen, "Expected ')' after arguments.");
        return callNode;
    }

    NodePtr Parser::parseIndex(NodePtr container) {
        auto indexNode = node<IndexNode>();
        indexNode->variable = std::move(container);
        indexNode->index = parseExpression(0);
        consume(Word::RightBracket, "Expected ']' after index.");
        return indexNode;
    }

    NodePtr Parser::parsePrimary() {
        if (match(Word::Null)       ||
            match(Word::True)       ||
            match(Word::False)      ||
            match(Word::Number)     ||
            match(Word::String)     ||
            match(Word::Character)  ||
            match(Word::Identifier)   )
            return node<LiteralNode>(previous());

        if (match(Word::LeftBracket)) return parseArray();
        if (match(Word::LeftBrace))   return parseDict();

        if (match(Word::LeftParen)) {
            NodePtr expr = parseExpression(0);
            consume(Word::RightParen, "Expected ')' after expression.");
            return expr;
        }

        throw error(peek(), "Expected expression.");
    }

    NodePtr Parser::parseUnary() {
        if (match(Word::Bang) || match(Word::BitNot) || match(Word::Minus)) {
            const Token op = previous();
            NodePtr operand = parseUnary();
            auto unode = node<UnaryNode>();
            unode->op = op.word;
            unode->operand = std::move(operand);
            return unode;
        }
        return parsePrimary();
    }

    NodePtr Parser::parseDict() {
        auto dict = node<DictLiteralNode>();

        if (!check(Word::RightBrace)) {
            do {
                NodePtr key = parseExpression();
                consume(Word::Colon, "Expected ':' after dictionary key.");
                NodePtr value = parseExpression();
                dict->pairs.emplace_back(std::move(key), std::move(value));
            } while (match(Word::Comma));
        }

        consume(Word::RightBrace, "Expected '}' after dictionary pairs.");
        return dict;
    }

    NodePtr Parser::parseArray() {
        auto array = node<ArrayLiteralNode>();

        if (!check(Word::RightBracket)) {
            do {
                array->items.push_back(parseExpression());
            } while (match(Word::Comma));
        }

        consume(Word::RightBracket, "Expected ']' after array elements.");
        return array;
    }

}
