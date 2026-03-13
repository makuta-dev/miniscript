#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "miniscript/Lexer.h"
#include "miniscript/Parser.h"
#include "miniscript/Printer.h"

void compile(const std::string& path) {
    const auto content = (std::stringstream() << std::ifstream(path).rdbuf()).str();
    const auto tokens = ms::Lexer(content).getTokens();
    if (const auto ast_root = ms::Parser(tokens).parse()){
        auto printer = ms::Printer();
        ast_root->accept(printer);
    } else {
        std::cout << "Bad AST" << std::endl;
    }
}

int main() {
    compile("/tmp/temp.ms");
    return 0;
}

// std::string(EXAMPLES_DIR)