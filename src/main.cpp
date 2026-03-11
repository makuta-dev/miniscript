#include <iostream>

#include "miniscript/Lexer.h"

const auto code = R"(let a = 5 a <<= 56 a >>>= 2)";

int main() {
    ms::Token t{};
    auto lexer = ms::Lexer(code);
    while (lexer.nextToken(t)) {
        std::cout << ms::toString(t) << std::endl;
    }
    return 0;
}