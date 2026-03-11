#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "miniscript/Lexer.h"

void compile(const std::string& path) {
    std::cout << "Path: " << path << std::endl;

    ms::Token t{};
    const auto content = (std::stringstream() << std::ifstream(path).rdbuf()).str();
    auto lexer = ms::Lexer(content);
    while (lexer.nextToken(t)) {
        std::cout << ms::toString(t) << std::endl;
    }
}

int main() {
    compile(std::string(EXAMPLES_DIR) + "/variables.ms");
    return 0;
}