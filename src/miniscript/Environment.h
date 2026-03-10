#ifndef MINISCRIPT_ENVIRONMENT_H
#define MINISCRIPT_ENVIRONMENT_H

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "miniscript/Value.h"

namespace ms {

    struct Environment {
        std::unordered_map<std::string, Value> values;
        std::unordered_set<std::string> constants;
        std::shared_ptr<Environment> enclosing;

        void define(const std::string& name, Value val, bool is_const);
        bool assign(const std::string& name, Value val);
    };

}

#endif //MINISCRIPT_ENVIRONMENT_H