#ifndef MINISCRIPT_VISITOR_H
#define MINISCRIPT_VISITOR_H

namespace miniscript {

    struct ImportNode;

    struct LiteralNode;
    struct ArrayLiteralNode;
    struct DictLiteralNode;

    struct ArgumentNode;
    struct FunctionNode;
    struct BlockNode;

    struct VariableNode;
    struct BinaryNode;
    struct UnaryNode;
    struct CallNode;
    struct WhileNode;
    struct ForNode;
    struct AssignNode;
    struct ReturnNode;
    struct IndexNode;
    struct BreakNode;
    struct ContinueNode;
    struct IfNode;

    struct Visitor {
        virtual ~Visitor() = default;

        virtual void visit(const LiteralNode&) = 0;
        virtual void visit(const ArrayLiteralNode&) = 0;
        virtual void visit(const DictLiteralNode&) = 0;
        virtual void visit(const ArgumentNode&) = 0;
        virtual void visit(const FunctionNode&) = 0;
        virtual void visit(const VariableNode&) = 0;
        virtual void visit(const BinaryNode&) = 0;
        virtual void visit(const UnaryNode&) = 0;
        virtual void visit(const CallNode&) = 0;
        virtual void visit(const WhileNode&) = 0;
        virtual void visit(const ForNode&) = 0;
        virtual void visit(const AssignNode&) = 0;
        virtual void visit(const ReturnNode&) = 0;
        virtual void visit(const BreakNode&) = 0;
        virtual void visit(const ContinueNode&) = 0;
        virtual void visit(const IndexNode&) = 0;
        virtual void visit(const BlockNode&) = 0;
        virtual void visit(const ImportNode&) = 0;
        virtual void visit(const IfNode&) = 0;
    };

}

#endif //MINISCRIPT_VISITOR_H