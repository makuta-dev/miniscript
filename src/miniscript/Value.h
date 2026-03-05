#ifndef MINISCRIPT_VALUE_H
#define MINISCRIPT_VALUE_H

#include <memory>
#include <string>

namespace miniscript {

    enum class ValueType {
        Null,
        Bool,
        Char,
        Integer,
        Real,
        String,
        Array,
        Dict
    };

    struct IValue;

    using ValuePtr = std::shared_ptr<IValue>;

    struct IValue {
        virtual ~IValue() = default;

        [[nodiscard]] virtual ValueType getType() const = 0;
        [[nodiscard]] virtual std::string toString() const = 0;
        [[nodiscard]] virtual std::size_t hash() const = 0;
        [[nodiscard]] virtual bool equals(const ValuePtr& other) const = 0;

        [[nodiscard]] virtual ValuePtr at(const ValuePtr&) const {
            return nullptr;
        }

        [[nodiscard]] virtual bool isTruthy() const {
            return true;
        }
    };

}

#endif //MINISCRIPT_VALUE_H