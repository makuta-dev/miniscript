#include "miniscript/Scope.h"

namespace miniscript {

    Scope::Scope(ScopePtr parent) : m_parent(std::move(parent)) {}

    void Scope::putVariable(const std::string& name, const ValuePtr& value) {
        m_variables[name] = value;
    }

    void Scope::putFunction(const std::string& name, NodePtr value) {
        m_functions[name] = std::move(value);
    }

    ValuePtr Scope::getVariable(const std::string& name) {
        if (m_variables.contains(name)) {
            return m_variables[name];
        }
        if (m_parent) {
            return m_parent->getVariable(name);
        }
        throw std::runtime_error("Variable " + name + " not found");
    }

    NodePtr Scope::getFunction(const std::string& name) {
        if (m_functions.contains(name)) {
            return std::move(m_functions[name]);
        }
        if (m_parent) {
            return m_parent->getFunction(name);
        }
        throw std::runtime_error("Function " + name + " not found");
    }

    bool Scope::delVariable(const std::string& name) {
        if (m_variables.contains(name)) {
            m_variables.erase(name);
            return true;
        }
        if (m_parent) {
            return m_parent->delVariable(name);
        }
        return false;
    }

    bool Scope::delFunction(const std::string& name) {
        if (m_functions.contains(name)) {
            m_functions.erase(name);
            return true;
        }
        if (m_parent) {
            return m_parent->delFunction(name);
        }
        return false;
    }

}