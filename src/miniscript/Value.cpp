#include "miniscript/Value.h"

#include <sstream>
#include <utility>

#include "Scope.h"

namespace miniscript {
    ValueType NullValue::getType() const {
        return ValueType::Null;
    }

    std::string NullValue::toString() const {
        return "null";
    }

    std::size_t NullValue::hash() const {
        return 0;
    }

    bool NullValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        return getType() == other->getType();
    }

    ValuePtr NullValue::instance() {
        static auto nullValue = std::make_shared<NullValue>();
        return nullValue;
    }

    // #########################################################

    BoolValue::BoolValue(const bool value) : m_value(value) {}

    ValueType BoolValue::getType() const {
        return ValueType::Bool;
    }

    std::string BoolValue::toString() const {
        return m_value ? "true" : "false";
    }

    std::size_t BoolValue::hash() const {
        return std::hash<bool>{}(m_value);
    }

    bool BoolValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<BoolValue*>(other.get())->getValue();
        }
        return false;
    }

    bool BoolValue::getValue() const {
        return m_value;
    }

    bool BoolValue::isTruthy() const {
        return m_value;
    }

    // #########################################################

    CharValue::CharValue(const uint32_t value) : m_value(value) {}

    ValueType CharValue::getType() const {
        return ValueType::Char;
    }

    std::string CharValue::toString() const {
        return {1, static_cast<char>(m_value)};
    }

    std::size_t CharValue::hash() const {
        return std::hash<uint32_t>{}(m_value);
    }

    bool CharValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<CharValue*>(other.get())->getValue();
        }
        return false;
    }

    bool CharValue::isTruthy() const {
        return m_value != 0;
    }

    uint32_t CharValue::getValue() const {
        return m_value;
    }

    // #########################################################

    IntValue::IntValue(const int64_t value) : m_value(value) {}

    ValueType IntValue::getType() const {
        return ValueType::Integer;
    }

    std::string IntValue::toString() const {
        return std::to_string(m_value);
    }

    std::size_t IntValue::hash() const {
        return std::hash<int64_t>{}(m_value);
    }

    bool IntValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<IntValue*>(other.get())->getValue();
        }
        return false;
    }

    bool IntValue::isTruthy() const {
        return m_value != 0;
    }

    int64_t IntValue::getValue() const {
        return m_value;
    }

    // #########################################################

    RealValue::RealValue(const double value) : m_value(value) {}

    ValueType RealValue::getType() const {
        return ValueType::Real;
    }

    std::string RealValue::toString() const {
        return std::to_string(m_value);
    }

    std::size_t RealValue::hash() const {
        return std::hash<double>{}(m_value);
    }

    bool RealValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<RealValue*>(other.get())->getValue();
        }
        return false;
    }

    bool RealValue::isTruthy() const {
        return m_value != 0.0;
    }

    double RealValue::getValue() const {
        return m_value;
    }

    // #########################################################

    StrValue::StrValue(std::string value) : m_value(std::move(value)) {}

    ValueType StrValue::getType() const {
        return ValueType::String;
    }

    std::string StrValue::toString() const {
        return m_value;
    }

    std::size_t StrValue::hash() const {
        return std::hash<std::string>{}(m_value);
    }

    bool StrValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<StrValue*>(other.get())->getValue();
        }
        return false;
    }

    bool StrValue::isTruthy() const {
        return !m_value.empty();
    }

    ValuePtr StrValue::at(const ValuePtr& index) const {
        if (!index) {
            return nullptr;
        }
        if (index->getType() == ValueType::Integer) {
            if (const auto i = dynamic_cast<const IntValue*>(index.get())->getValue();
                !m_value.empty() && i < m_value.length()) {
                return std::make_shared<CharValue>(m_value[i]);
            }
            return std::make_shared<NullValue>();
        }
        return nullptr;
    }

    std::string StrValue::getValue() const {
        return m_value;
    }

    // #########################################################

    ArrValue::ArrValue(std::vector<ValuePtr> value) : m_value(std::move(value)) {}

    ValueType ArrValue::getType() const {
        return ValueType::Array;
    }

    std::string ArrValue::toString() const {
        std::stringstream ss;
        ss << "[ ";
        for (const auto& value : m_value) {
            ss << value->toString();
            if (value != m_value.back()) {
                ss << ", ";
            }
        }
        ss << " ]";
        return ss.str();
    }

    std::size_t ArrValue::hash() const {
        std::size_t seed = m_value.size();

        for (const auto& element : m_value) {
            const std::size_t h = element ? element->hash() : 0x0;
            seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }

    bool ArrValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<ArrValue*>(other.get())->getValue();
        }
        return false;
    }

    bool ArrValue::isTruthy() const {
        return !m_value.empty();
    }

    ValuePtr ArrValue::at(const ValuePtr& index) const {
        if (!index) {
            return nullptr;
        }
        if (index->getType() == ValueType::Integer) {
            if (const auto i = dynamic_cast<const IntValue*>(index.get())->getValue();
                !m_value.empty() && i < m_value.size()) {
                return m_value[i];
            }
            return std::make_shared<NullValue>();
        }
        return nullptr;
    }

    std::vector<ValuePtr> ArrValue::getValue() const {
        return m_value;
    }

    // #########################################################

    DictValue::DictValue(DictType value) : m_value(std::move(value)) {}

    ValueType DictValue::getType() const {
        return ValueType::Dict;
    }

    std::string DictValue::toString() const {
        if (m_value.empty()) return "{}";

        std::string res = "{";
        bool first = true;
        for (const auto& [key, val] : m_value) {
            if (!first) res += ", ";
            res += key ? key->toString() : "null";
            res += ": ";
            res += val ? val->toString() : "null";
            first = false;
        }
        res += "}";
        return res;
    }

    std::size_t DictValue::hash() const {
        std::size_t seed = 0;

        for (const auto& [key, val] : m_value) {
            std::size_t pair_hash = key ? key->hash() : 0;

            const std::size_t v_hash = val ? val->hash() : 0;
            pair_hash ^= v_hash + 0x9e3779b9 + (pair_hash << 6) + (pair_hash >> 2);

            seed += pair_hash;
        }

        return seed;
    }

    bool DictValue::equals(const ValuePtr &other) const {
        if (!other) {
            return false;
        }
        if (getType() == other->getType()) {
            return m_value == dynamic_cast<DictValue*>(other.get())->getValue();
        }
        return false;
    }

    bool DictValue::isTruthy() const {
        return !m_value.empty();
    }

    ValuePtr DictValue::at(const ValuePtr& index) const {
        if (!index) {
            return nullptr;
        }
        if (m_value.contains(index)) {
            return m_value.at(index);
        }
        return nullptr;
    }

    DictValue::DictType DictValue::getValue() const {
        return m_value;
    }

    // #########################################################

    FuncValue::FuncValue(NativeFn value) : m_value(std::move(value)) {}

    ValueType FuncValue::getType() const {
        return ValueType::NativeFunc;
    }

    std::string FuncValue::toString() const {
        return "<native function>";
    }

    std::size_t FuncValue::hash() const {
        return 0;
    }

    bool FuncValue::equals(const ValuePtr &other) const {
        return false;
    }

    bool FuncValue::isTruthy() const {
        return true;
    }

    FuncValue::NativeFn FuncValue::getValue() const {
        return m_value;
    }

    // #########################################################

    UFuncValue::UFuncValue(const FunctionNode* value, ScopePtr scope) : m_value(value), m_scope(std::move(scope)) {}

    ValueType UFuncValue::getType() const {
        return ValueType::Func;
    }

    std::string UFuncValue::toString() const {
        return "<function>";
    }

    std::size_t UFuncValue::hash() const {
        return 0;
    }

    bool UFuncValue::equals(const ValuePtr &other) const {
        if (other != nullptr && other->getType() == ValueType::Func) {
            return m_value == dynamic_cast<UFuncValue*>(other.get())->getValue();
        }
        return false;
    }

    bool UFuncValue::isTruthy() const {
        return true;
    }

    const FunctionNode* UFuncValue::getValue() const {
        return m_value;
    }

    ScopePtr UFuncValue::getDefinitionScope() const {
        return m_scope;
    }

}
