cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(miniscript)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(miniscript
        src/miniscript/Environment.h
        src/miniscript/Lexer.h
        src/miniscript/Token.h
        src/miniscript/Value.h
        src/miniscript/Word.h

        src/miniscript/Environment.cpp
        src/miniscript/Lexer.cpp
        src/miniscript/Token.cpp
        src/miniscript/Word.cpp

        src/main.cpp
        src/miniscript/ASTree.h
)

target_include_directories(miniscript PRIVATE src)
target_compile_definitions(miniscript PRIVATE EXAMPLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/examples")
