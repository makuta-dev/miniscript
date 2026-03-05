#ifndef MINISCRIPT_ASTREE_H
#define MINISCRIPT_ASTREE_H

#include <memory>
#include <vector>

#include "miniscript/Token.h"
#include "miniscript/Visitor.h"

namespace miniscript {

    struct ASTNode {
        virtual ~ASTNode() = default;

        virtual void accept(Visitor&) = 0;
    };

    using NodePtr = std::unique_ptr<ASTNode>;
    using NodeVec = std::vector<NodePtr>;
    using NodePair = std::pair<NodePtr,NodePtr>;

    struct LiteralNode : ASTNode {
        Token token;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ArrayLiteralNode : ASTNode {
        NodeVec items;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct DictLiteralNode : ASTNode {
        std::vector<NodePair> pairs;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ArgumentNode : ASTNode {
        std::string name;
        NodePtr value;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct FunctionNode : ASTNode {
        std::string name;
        NodeVec arguments;
        NodePtr body;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct VariableNode : ASTNode {
        std::string name;
        NodePtr value;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct BinaryNode : ASTNode {
        Word op;
        NodePtr left;
        NodePtr right;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct UnaryNode : ASTNode {
        Word op;
        NodePtr operand;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct CallNode : ASTNode {
        NodePtr name;
        NodeVec arguments;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct AssignNode : ASTNode {
        NodePtr name;
        NodePtr value;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct WhileNode : ASTNode {
        NodePtr condition;
        NodePtr body;
        bool is_do_while = false;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ForNode : ASTNode {
        NodePtr variable;
        NodePtr condition;
        NodePtr increment;
        NodePtr body;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ReturnNode : ASTNode {
        NodePtr variable;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct BreakNode : ASTNode {
        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ContinueNode : ASTNode {
        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct IndexNode : ASTNode {
        NodePtr variable;
        NodePtr index;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct BlockNode : ASTNode {
        NodeVec statements;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

    struct ImportNode : ASTNode {
        std::string path;

        void accept(Visitor& v) override {
            v.visit(*this);
        }
    };

}

#endif //MINISCRIPT_ASTREE_H