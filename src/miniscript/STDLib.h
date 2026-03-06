#ifndef MINISCRIPT_STDLIB_H
#define MINISCRIPT_STDLIB_H

#include "miniscript/Value.h"

namespace miniscript::stdlib {

    ValuePtr print(const std::vector<ValuePtr>& args);
    ValuePtr println(const std::vector<ValuePtr>& args);
    ValuePtr toInt(const std::vector<ValuePtr>& args);
    ValuePtr toReal(const std::vector<ValuePtr>& args);

}

#endif //MINISCRIPT_STDLIB_H