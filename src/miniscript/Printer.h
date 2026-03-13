#ifndef MINISCRIPT_PRINTER_H
#define MINISCRIPT_PRINTER_H

#include "miniscript/ASTree.h"

namespace ms {

    class Printer final : public IVisitor {
    public:
        void visit(const ProgramNode &) override;
        void visit(const LiteralNode&) override;
        void visit(const ALiteralNode&) override;
        void visit(const PLiteralNode&) override;
        void visit(const DLiteralNode&) override;
        void visit(const ConstNode&) override;
        void visit(const VariableNode&) override;
        void visit(const BinaryNode&) override;
        void visit(const UnaryNode&) override;
        void visit(const AccessNode&) override;
        void visit(const CallNode&) override;
        void visit(const IfNode&) override;
        void visit(const WhileNode&) override;
        void visit(const ForNode&) override;
        void visit(const MatchNode&) override;
        void visit(const BlockNode&) override;
        void visit(const FunctionNode&) override;
        void visit(const ReturnNode&) override;
        void visit(const RangeNode&) override;
        void visit(const IndexNode&) override;
        void visit(const AssignNode&) override;
        void visit(const GetNode&) override;
        void visit(const GroupingNode&) override;
        void visit(const BreakNode&) override;
        void visit(const ContinueNode&) override;
        void visit(const InterpolatedStringNode&) override;
        void visit(const ExpressionStatementNode&) override;
    };

}

#endif //MINISCRIPT_PRINTER_H