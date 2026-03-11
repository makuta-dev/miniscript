#include <fstream>
#include <iostream>

#include "miniscript/Lexer.h"

void compile(const std::string& path) {
    std::cout << path << std::endl;
    if (std::ifstream file(path); file.is_open()) {
        int line_num = 0;
        std::string line;
        ms::Token t{};
        while (std::getline(file,line)) {
            line_num++;
            auto lexer = ms::Lexer(line,line_num);
            while (lexer.nextToken(t)) {
                std::cout << ms::toString(t) << std::endl;
            }
        }
        file.close();
    }
}

int main() {
    compile(std::string(EXAMPLES_DIR) + "/variables.ms");
    return 0;
}