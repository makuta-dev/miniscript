#include "miniscript/Interpreter.h"

namespace miniscript {

    void Interpreter::visit(const LiteralNode &) {

    }

    void Interpreter::visit(const ArrayLiteralNode &) {

    }

    void Interpreter::visit(const DictLiteralNode &) {

    }

    void Interpreter::visit(const ArgumentNode &) {

    }

    void Interpreter::visit(const FunctionNode &) {

    }

    void Interpreter::visit(const VariableNode &) {

    }

    void Interpreter::visit(const BinaryNode &) {

    }

    void Interpreter::visit(const UnaryNode &) {

    }

    void Interpreter::visit(const CallNode &) {

    }

    void Interpreter::visit(const WhileNode &) {

    }

    void Interpreter::visit(const ForNode &) {

    }

    void Interpreter::visit(const AssignNode &) {

    }

    void Interpreter::visit(const ReturnNode &) {

    }

    void Interpreter::visit(const BreakNode &) {

    }

    void Interpreter::visit(const ContinueNode &) {

    }

    void Interpreter::visit(const IndexNode &) {

    }

    void Interpreter::visit(const BlockNode &) {

    }

    void Interpreter::visit(const ImportNode &) {

    }

    void Interpreter::visit(const IfNode&) {

    }

    ValuePtr Interpreter::evaluate(ASTNode* node) {
        if (!node) return NullValue::instance();
        node->accept(*this);
        return m_lastValue;
    }

}