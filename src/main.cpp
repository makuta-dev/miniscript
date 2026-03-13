#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "miniscript/Lexer.h"
#include "miniscript/Parser.h"
#include "miniscript/Printer.h"

void compile(const std::string& path) {
    std::cout << "Path: " << path << std::endl;

    ms::Token t{};
    const auto content = (std::stringstream() << std::ifstream(path).rdbuf()).str();
    auto tokens = std::vector<ms::Token>();
    auto lexer = ms::Lexer(content);
    while (lexer.nextToken(t)) {
        tokens.push_back(t);
    }
    auto parser = ms::Parser(tokens);
    auto printer = ms::Printer();
    if (const auto ast_root = parser.parse()){
        ast_root->accept(printer);
    } else {
        std::cout << "Bad AST" << std::endl;
    }
}

int main() {
    compile(std::string(EXAMPLES_DIR) + "/variables.ms");
    return 0;
}