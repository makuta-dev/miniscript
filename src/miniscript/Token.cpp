#include "miniscript/Token.h"

#include <iomanip>

namespace miniscript {

    // format: [Line 1:10] IDENTIFIER : "myVar"
    std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "[" << token.line << ":" << token.column << "] "
           << to_string(token.word);

        if (!token.value.empty()) {
            os << " : \"" << token.value << "\"";
        }

        return os;
    }

}