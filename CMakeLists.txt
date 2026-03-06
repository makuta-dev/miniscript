cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(miniscript)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(miniscript
        # headers
        src/miniscript/ASTree.h
        src/miniscript/Interpreter.h
        src/miniscript/Lexer.h
        src/miniscript/Parser.h
        src/miniscript/Scope.h
        src/miniscript/STDLib.h
        src/miniscript/Token.h
        src/miniscript/Trie.h
        src/miniscript/Value.h
        src/miniscript/Visitor.h
        src/miniscript/Word.h

        # impl
        src/miniscript/Interpreter.cpp
        src/miniscript/Lexer.cpp
        src/miniscript/Parser.cpp
        src/miniscript/Scope.cpp
        src/miniscript/STDLib.cpp
        src/miniscript/Token.cpp
        src/miniscript/Trie.cpp
        src/miniscript/Value.cpp
        src/miniscript/Word.cpp

        src/main.cpp
)

target_include_directories(miniscript PRIVATE src)
