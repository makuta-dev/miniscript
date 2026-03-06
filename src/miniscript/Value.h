#ifndef MINISCRIPT_VALUE_H
#define MINISCRIPT_VALUE_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace miniscript {

    enum class ValueType {
        Null,
        Bool,
        Char,
        Integer,
        Real,
        String,
        Array,
        Dict,
        Function
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

    struct ValueHash {
        std::size_t operator()(const ValuePtr &value) const {
            if (!value) return 0;
            return value->hash();
        }
    };

    struct ValueEqual {
        bool operator()(const ValuePtr& lhs, const ValuePtr& rhs) const {
            if (lhs == rhs) return true;
            if (!lhs || !rhs) return false;
            return lhs->equals(rhs);
        }
    };

    struct NullValue final : IValue {
        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;

        static ValuePtr instance();
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
        explicit StrValue(std::string  value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;
        [[nodiscard]] ValuePtr at(const ValuePtr&) const override;

        [[nodiscard]] std::string getValue() const;

    private:
        std::string m_value;
    };

    struct ArrValue final : IValue {
        explicit ArrValue(std::vector<ValuePtr> value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;
        [[nodiscard]] ValuePtr at(const ValuePtr&) const override;

        [[nodiscard]] std::vector<ValuePtr> getValue() const;

    private:
        std::vector<ValuePtr> m_value;
    };

    struct DictValue final : IValue {
        using DictType = std::unordered_map<ValuePtr,ValuePtr, ValueHash, ValueEqual>;

        explicit DictValue(DictType value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;
        [[nodiscard]] ValuePtr at(const ValuePtr&) const override;

        [[nodiscard]] DictType getValue() const;

    private:
        DictType m_value;
    };

    struct FuncValue final : IValue {
        using NativeFn = std::function<ValuePtr(const std::vector<ValuePtr>&)>;

        explicit FuncValue(NativeFn value);

        [[nodiscard]] ValueType getType() const override;
        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] std::size_t hash() const override;
        [[nodiscard]] bool equals(const ValuePtr &other) const override;
        [[nodiscard]] bool isTruthy() const override;

        [[nodiscard]] NativeFn getValue() const;

    private:
        NativeFn m_value;
    };

}

#endif //MINISCRIPT_VALUE_H