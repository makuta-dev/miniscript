#include "STDLib.h"

#include <iostream>

namespace miniscript::stdlib {

    ValuePtr print(const std::vector<ValuePtr>& args) {
        for (const auto& item : args) {
            std::cout << item->toString() << "";
        }
        return NullValue::instance();
    }

    ValuePtr println(const std::vector<ValuePtr>& args) {
        for (const auto& item : args) {
            std::cout << item->toString() << std::endl;
        }
        return NullValue::instance();
    }

    ValuePtr toInt(const std::vector<ValuePtr>& args) {
        if (args.empty())
            return std::make_shared<IntValue>(0);
        if (args.size() == 1) {
            const auto& item = args.at(0);
            if (item->getType() == ValueType::Integer) {
                return item;
            }
            if (item->getType() == ValueType::Real) {
                const auto value = dynamic_cast<const RealValue*>(item.get())->getValue();
                return std::make_shared<IntValue>(static_cast<int64_t>(value));
            }
            if (item->getType() == ValueType::String) {
                const auto value = dynamic_cast<const StrValue*>(item.get())->getValue();
                return std::make_shared<IntValue>(static_cast<int64_t>(std::stod(value)));
            }
        }
        return NullValue::instance();
    }

    ValuePtr toReal(const std::vector<ValuePtr>& args) {
        if (args.empty())
            return std::make_shared<RealValue>(0);
        if (args.size() == 1) {
            const auto& item = args.at(0);
            if (item->getType() == ValueType::Real) {
                return item;
            }
            if (item->getType() == ValueType::Integer) {
                const auto value = dynamic_cast<const IntValue*>(item.get())->getValue();
                return std::make_shared<RealValue>(static_cast<double>(value));
            }
            if (item->getType() == ValueType::String) {
                const auto value = dynamic_cast<const StrValue*>(item.get())->getValue();
                return std::make_shared<RealValue>(std::stod(value));
            }
        }
        return NullValue::instance();
    }

}
