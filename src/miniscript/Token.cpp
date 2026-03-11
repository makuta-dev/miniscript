#include "Token.h"

#include <sstream>

namespace ms {

    std::string toString(const Token& token) {
        std::ostringstream oss;
        oss << '[' << token.line << ':' << token.column << ']' << ' ';
        oss << toString(token.word) << ' ';
        if (!token.value.empty())
            oss<< token.value;
        return oss.str();
    }

}
