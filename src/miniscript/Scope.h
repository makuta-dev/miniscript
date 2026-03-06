#ifndef MINISCRIPT_SCOPE_H
#define MINISCRIPT_SCOPE_H

#include <memory>
#include <unordered_map>

#include "miniscript/Value.h"

namespace miniscript {

    class Scope;

    using ScopePtr = std::shared_ptr<Scope>;

    class Scope final {
    public:
        explicit Scope(ScopePtr parent);

        void put(const std::string& name, ValuePtr value);
        ValuePtr get(const std::string& name);
        bool remove(const std::string& name);

    private:
        ScopePtr m_parent;
        std::unordered_map<std::string, ValuePtr> m_variables;
    };

}

#endif //MINISCRIPT_SCOPE_H