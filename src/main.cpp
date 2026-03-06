#include <expected>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <print>

#include "miniscript/Interpreter.h"
#include "miniscript/Lexer.h"
#include "miniscript/Parser.h"

std::expected<std::string, std::string> read_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        return std::unexpected("Could not open file: " + path);
    }

    const std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer;
    buffer.reserve(static_cast<size_t>(size));

    buffer.assign(std::istreambuf_iterator(file),
                  std::istreambuf_iterator<char>());

    return buffer;
}

void run(const std::string_view source) {
    miniscript::Lexer lexer(source);
    auto parser = miniscript::Parser(lexer.tokenize());
    if (const auto program = parser.parse()){
        auto interpreter = miniscript::Interpreter();
        program->accept(interpreter);
    }else {
        std::println(std::cerr, "NullPointer received");
    }
}

void run_repl() {
    std::print("Miniscript REPL (C++23)\n");
    std::print("Type 'exit' to quit.\n");

    std::string line;
    while (true) {
        std::print("> ");
        if (!std::getline(std::cin, line) || line == "exit") break;
        if (line.empty()) continue;

        run(line);
    }
}

void run_file(const std::string& path) {
    auto result = read_file(path);
    if (!result) {
        std::print(std::cerr, "Error: {}\n", result.error());
        return;
    }
    run(result.value());
}

int main(const int argc, const char** argv) {
    if (argc > 1) {
        run_file(argv[1]);
    } else {
        run_repl();
    }
    return 0;
}