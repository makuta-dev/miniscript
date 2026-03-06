#ifndef MINISCRIPT_INTERPRETER_H
#define MINISCRIPT_INTERPRETER_H

#include "miniscript/ASTree.h"

namespace miniscript {

    class Interpreter final : public Visitor{
    public:
        void visit(const LiteralNode &) override;
        void visit(const ArrayLiteralNode &) override;
        void visit(const DictLiteralNode &) override;
        void visit(const ArgumentNode &) override;
        void visit(const FunctionNode &) override;
        void visit(const VariableNode &) override;
        void visit(const BinaryNode &) override;
        void visit(const UnaryNode &) override;
        void visit(const CallNode &) override;
        void visit(const WhileNode &) override;
        void visit(const ForNode &) override;
        void visit(const AssignNode &) override;
        void visit(const ReturnNode &) override;
        void visit(const BreakNode &) override;
        void visit(const ContinueNode &) override;
        void visit(const IndexNode &) override;
        void visit(const BlockNode &) override;
        void visit(const ImportNode &) override;
        void visit(const IfNode&) override;
    };

}

#endif //MINISCRIPT_INTERPRETER_H