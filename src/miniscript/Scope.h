#ifndef MINISCRIPT_SCOPE_H
#define MINISCRIPT_SCOPE_H

#include <memory>
#include <unordered_map>

#include "ASTree.h"
#include "Value.h"

namespace miniscript {

    class Scope;

    using ScopePtr = std::shared_ptr<Scope>;

    class Scope final {
    public:
        explicit Scope(ScopePtr parent);

        void putVariable(const std::string& name, const ValuePtr& value);
        void putFunction(const std::string& name, NodePtr value);

        ValuePtr getVariable(const std::string& name);
        NodePtr getFunction(const std::string& name);

        bool delVariable(const std::string& name);
        bool delFunction(const std::string& name);

    private:
        ScopePtr m_parent;
        std::unordered_map<std::string, ValuePtr> m_variables;
        std::unordered_map<std::string, NodePtr> m_functions;
    };

}

#endif //MINISCRIPT_SCOPE_H