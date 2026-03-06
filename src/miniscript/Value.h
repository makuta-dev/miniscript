#ifndef MINISCRIPT_VALUE_H
#define MINISCRIPT_VALUE_H

#include <iomanip>
#include <memory>
#include <sstream>
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
            return false;
        }
    };

    struct NullValue final : IValue {
        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
    };

    struct BoolValue final : IValue {
        explicit BoolValue(bool value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;

        [[nodiscard]] bool getValue() const;

    private:
        bool m_value;
    };

    struct CharValue final : IValue {
        explicit CharValue(uint32_t value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;

        [[nodiscard]] uint32_t getValue() const;

    private:
        uint32_t m_value;
    };

    struct IntValue final : IValue {
        explicit IntValue(int64_t value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;

        [[nodiscard]] int64_t getValue() const;

    private:
        int64_t m_value;
    };

    struct RealValue final : IValue {
        explicit RealValue(double value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;

        [[nodiscard]] double getValue() const;

    private:
        double m_value;
    };

    struct StrValue final : IValue {

    };

    struct ArrValue final : IValue {

    };

    struct DictValue final : IValue {

    };


}

#endif //MINISCRIPT_VALUE_H