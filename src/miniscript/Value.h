#ifndef MINISCRIPT_VALUE_H
#define MINISCRIPT_VALUE_H

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace ms {

    struct Value;
    struct Pair { Value* first; Value* second; };

    // Use a recursive alias for complex structures
    using Array  = std::vector<Value>;
    using Dict   = std::unordered_map<std::string, Value>;
    using Lambda = std::function<Value(const std::vector<Value>&)>;

    struct Value {
        std::variant<
            std::monostate, // null
            bool,           // bool
            double,         // number
            std::string,    // str
            std::shared_ptr<Array>,
            std::shared_ptr<Dict>,
            std::shared_ptr<Pair>,
            Lambda
        > data;

        // C++23 utility for easy type checking
        template<typename T> bool is() const { return std::holds_alternative<T>(data); }
    };

}

#endif //MINISCRIPT_VALUE_H