#ifndef MINISCRIPT_ASTREE_H
#define MINISCRIPT_ASTREE_H

#include <memory>
#include <vector>

namespace ms {

    struct ProgramNode;

    struct IVisitor {
        virtual ~IVisitor() = default;

        virtual void visit(const ProgramNode&) = 0;
    };

    struct ASTNode {
        virtual ~ASTNode() = default;

        virtual void accept(IVisitor&) = 0;
    };

    using NodePtr = std::unique_ptr<ASTNode>;

    struct ProgramNode : ASTNode {
        std::vector<NodePtr> declarations;

        void accept(IVisitor& v) override {
            v.visit(*this);
        }
    };

}

#endif //MINISCRIPT_ASTREE_H