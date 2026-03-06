#include "miniscript/Value.h"

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

}