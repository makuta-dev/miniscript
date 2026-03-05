cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(miniscript)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(miniscript
        # headers
        src/miniscript/Lexer.h
        src/miniscript/Token.h
        src/miniscript/Trie.h
        src/miniscript/Word.h

        # impl
        src/miniscript/Lexer.cpp
        src/miniscript/Token.cpp
        src/miniscript/Trie.cpp
        src/miniscript/Word.cpp

        src/main.cpp
        src/miniscript/ASTree.h
        src/miniscript/Visitor.h
)

target_include_directories(miniscript PRIVATE src)
