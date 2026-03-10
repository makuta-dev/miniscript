#include "Environment.h"

namespace ms {

    void Environment::define(const std::string& name, Value val, const bool is_const) {
        values[name] = std::move(val);
        if (is_const) constants.insert(name);
    }

    bool Environment::assign(const std::string& name, Value val) {
        if (constants.contains(name)) return false;
        if (values.contains(name)) {
            values[name] = std::move(val);
            return true;
        }

        if (enclosing) {
            return enclosing->assign(name, std::move(val));
        }

        return false;
    }

}