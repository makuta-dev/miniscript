#include "Printer.h"

#include <print>

namespace ms {

    void Printer::visit(const ProgramNode &) {
        std::println("Program:");
    }

    void Printer::visit(const LiteralNode&) {

    }

    void Printer::visit(const ALiteralNode&) {

    }

    void Printer::visit(const PLiteralNode&) {

    }

    void Printer::visit(const DLiteralNode&) {

    }

    void Printer::visit(const ConstNode&) {

    }

    void Printer::visit(const VariableNode&) {

    }

    void Printer::visit(const BinaryNode&) {

    }

    void Printer::visit(const UnaryNode&) {

    }

    void Printer::visit(const AccessNode&) {

    }

    void Printer::visit(const CallNode&) {

    }

    void Printer::visit(const IfNode&) {

    }

    void Printer::visit(const WhileNode&) {

    }

    void Printer::visit(const ForNode&) {

    }

    void Printer::visit(const MatchNode&) {

    }

    void Printer::visit(const BlockNode&) {

    }

    void Printer::visit(const FunctionNode&) {

    }

    void Printer::visit(const ReturnNode&) {

    }

    void Printer::visit(const RangeNode&) {

    }

    void Printer::visit(const IndexNode&) {

    }

    void Printer::visit(const AssignNode&) {

    }

    void Printer::visit(const GetNode&) {

    }

    void Printer::visit(const GroupingNode&) {

    }

    void Printer::visit(const BreakNode&) {

    }

    void Printer::visit(const ContinueNode&) {

    }

    void Printer::visit(const InterpolatedStringNode&) {

    }

    void Printer::visit(const ExpressionStatementNode&) {

    }

}
