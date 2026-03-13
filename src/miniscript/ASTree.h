#ifndef MINISCRIPT_ASTREE_H
#define MINISCRIPT_ASTREE_H

#include <memory>
#include <vector>

#include "Token.h"

namespace ms {

    struct ProgramNode;
    struct LiteralNode;  // null, bool, number, string
    struct ALiteralNode; // array
    struct PLiteralNode; // pair
    struct DLiteralNode; // dict
    struct ConstNode;
    struct VariableNode;
    struct BinaryNode;
    struct UnaryNode;
    struct AccessNode;
    struct CallNode;
    struct IfNode;
    struct WhileNode;
    struct ForNode;
    struct MatchNode;
    struct BlockNode;
    struct FunctionNode;
    struct ReturnNode;
    struct RangeNode;
    struct IndexNode;
    struct AssignNode ;
    struct GetNode;
    struct GroupingNode;
    struct BreakNode;
    struct ContinueNode;
    struct InterpolatedStringNode;
    struct ExpressionStatementNode;

    struct IVisitor {
        virtual ~IVisitor() = default;

        virtual void visit(const ProgramNode&) = 0;
        virtual void visit(const LiteralNode&) = 0;
        virtual void visit(const ALiteralNode&) = 0;
        virtual void visit(const PLiteralNode&) = 0;
        virtual void visit(const DLiteralNode&) = 0;
        virtual void visit(const ConstNode&) = 0;
        virtual void visit(const VariableNode&) = 0;
        virtual void visit(const BinaryNode&) = 0;
        virtual void visit(const UnaryNode&) = 0;
        virtual void visit(const AccessNode&) = 0;
        virtual void visit(const CallNode&) = 0;
        virtual void visit(const IfNode&) = 0;
        virtual void visit(const WhileNode&) = 0;
        virtual void visit(const ForNode&) = 0;
        virtual void visit(const MatchNode&) = 0;
        virtual void visit(const BlockNode&) = 0;
        virtual void visit(const FunctionNode&) = 0;
        virtual void visit(const ReturnNode&) = 0;
        virtual void visit(const RangeNode&) = 0;
        virtual void visit(const IndexNode&) = 0;
        virtual void visit(const AssignNode&) = 0 ;
        virtual void visit(const GetNode&) = 0;
        virtual void visit(const GroupingNode&) = 0;
        virtual void visit(const BreakNode&) = 0;
        virtual void visit(const ContinueNode&) = 0;
        virtual void visit(const InterpolatedStringNode&) = 0;
        virtual void visit(const ExpressionStatementNode&) = 0;
    };

    struct ASTNode {
        virtual ~ASTNode() = default;

        virtual void accept(IVisitor&) = 0;
    };

    using NodePtr = std::unique_ptr<ASTNode>;
    using NodeVec = std::vector<NodePtr>;

    template <typename T, typename... Args>
    std::unique_ptr<T> node(Args... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    struct ProgramNode final : ASTNode {
        NodeVec declarations;

        explicit ProgramNode(NodeVec v) : declarations(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

    struct LiteralNode final : ASTNode {
        Token token;

        explicit LiteralNode(const Token &t) : token(t) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }

    };

    struct ALiteralNode final : ASTNode {
        NodeVec items;

        explicit ALiteralNode(NodeVec v) : items(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }

    };

    struct PLiteralNode final : ASTNode {
        NodePtr key;
        NodePtr value;

        explicit PLiteralNode(NodePtr k, NodePtr v) : key(std::move(k)), value(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

    struct DLiteralNode final : ASTNode {
        NodeVec items;

        explicit DLiteralNode(NodeVec v) : items(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

    struct ConstNode final : ASTNode {
        std::string name;
        NodePtr value;

        ConstNode(std::string n, NodePtr v) : name(std::move(n)), value(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

    struct VariableNode final : ASTNode {
        std::string name;
        NodePtr value;

        VariableNode(std::string n, NodePtr v) : name(std::move(n)), value(std::move(v)) {}

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

    struct BinaryNode final : ASTNode {
        NodePtr left;
        Token op;
        NodePtr right;

        BinaryNode(NodePtr l, const Token &o, NodePtr r)
            : left(std::move(l)), op(o), right(std::move(r)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct UnaryNode final : ASTNode {
        Token op;
        NodePtr right;
        bool postfix;

        UnaryNode(const Token &o, NodePtr r, const bool p = false)
            : op(o), right(std::move(r)), postfix(p) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct AccessNode final : ASTNode {
        std::string name;

        explicit AccessNode(std::string n) : name(std::move(n)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct CallNode final : ASTNode {
        NodePtr callee;
        NodeVec arguments;

        CallNode(NodePtr c, NodeVec a) : callee(std::move(c)), arguments(std::move(a)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct IfNode final : ASTNode {
        NodePtr condition;
        NodePtr thenBranch;
        NodePtr elseBranch;

        IfNode(NodePtr cond, NodePtr thenB, NodePtr elseB)
            : condition(std::move(cond)), thenBranch(std::move(thenB)), elseBranch(std::move(elseB)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct WhileNode final : ASTNode {
        NodePtr condition;
        NodePtr body;
        bool isDoWhile;

        WhileNode(NodePtr cond, NodePtr b, const bool dw = false)
            : condition(std::move(cond)), body(std::move(b)), isDoWhile(dw) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct ForNode final : ASTNode {
        std::vector<std::string> iterators;
        NodePtr iterable;
        NodePtr body;

        ForNode(std::vector<std::string> iters, NodePtr item, NodePtr b)
            : iterators(std::move(iters)), iterable(std::move(item)), body(std::move(b)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct MatchArm {
        NodePtr condition;
        NodePtr body;
    };

    struct MatchNode final : ASTNode {
        NodePtr expression;
        std::vector<MatchArm> arms;

        MatchNode(NodePtr expr, std::vector<MatchArm> a)
            : expression(std::move(expr)), arms(std::move(a)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct BlockNode final : ASTNode {
        NodeVec statements;

        explicit BlockNode(NodeVec s) : statements(std::move(s)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct FunctionNode final : ASTNode {
        std::string name;
        std::vector<std::string> params;
        NodePtr body;

        FunctionNode(std::string n, std::vector<std::string> p, NodePtr b)
            : name(std::move(n)), params(std::move(p)), body(std::move(b)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct ReturnNode final : ASTNode {
        NodePtr value;

        explicit ReturnNode(NodePtr v) : value(std::move(v)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct RangeNode final : ASTNode {
        NodePtr start;
        NodePtr end;
        NodePtr step;

        RangeNode(NodePtr s, NodePtr e, NodePtr st = nullptr)
            : start(std::move(s)), end(std::move(e)), step(std::move(st)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct IndexNode final : ASTNode {
        NodePtr iterable;
        NodePtr index;

        IndexNode(NodePtr coll, NodePtr idx)
            : iterable(std::move(coll)), index(std::move(idx)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct AssignNode final : ASTNode {
        NodePtr target;
        Token op;
        NodePtr value;

        AssignNode(NodePtr t, const Token &o, NodePtr val)
            : target(std::move(t)), op(o), value(std::move(val)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct GetNode final : ASTNode {
        NodePtr object;
        std::string property;

        GetNode(NodePtr obj, std::string prop)
            : object(std::move(obj)), property(std::move(prop)) {}

        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct GroupingNode final : ASTNode {
        NodePtr expression;

        explicit GroupingNode(NodePtr expr) : expression(std::move(expr)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct BreakNode final : ASTNode {
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct ContinueNode final : ASTNode {
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct InterpolatedStringNode final : ASTNode {
        NodeVec parts;

        explicit InterpolatedStringNode(NodeVec p) : parts(std::move(p)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

    struct ExpressionStatementNode final : ASTNode {
        NodePtr expression;

        explicit ExpressionStatementNode(NodePtr expr) : expression(std::move(expr)) {}
        void accept(IVisitor& v) override { v.visit(*this); }
    };

}

#endif //MINISCRIPT_ASTREE_H