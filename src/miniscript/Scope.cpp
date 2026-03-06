#include "miniscript/Scope.h"

#include <utility>
#include "miniscript/STDLib.h"

namespace miniscript {

    Scope::Scope(ScopePtr parent) : m_parent(std::move(parent)) {
        m_variables.emplace("help",     std::make_shared<FuncValue>(stdlib::help)   );
        m_variables.emplace("print",    std::make_shared<FuncValue>(stdlib::print)  );
        m_variables.emplace("println",  std::make_shared<FuncValue>(stdlib::println));
        m_variables.emplace("int",      std::make_shared<FuncValue>(stdlib::toInt)  );
        m_variables.emplace("real",     std::make_shared<FuncValue>(stdlib::toReal) );
    }

    void Scope::put(const std::string& name, ValuePtr value) {
        m_variables[name] = std::move(value);
    }

    ValuePtr Scope::get(const std::string& name) {
        if (m_variables.contains(name)) {
            return m_variables[name];
        }
        if (m_parent) {
            return m_parent->get(name);
        }
        throw std::runtime_error("Variable " + name + " not found");
    }

    bool Scope::remove(const std::string& name) {
        if (m_variables.contains(name)) {
            m_variables.erase(name);
            return true;
        }
        if (m_parent) {
            return m_parent->remove(name);
        }
        return false;
    }

}
