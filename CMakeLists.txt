cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(miniscript)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(miniscript
        src/miniscript/Environment.h
        src/miniscript/Value.h

        src/miniscript/Environment.cpp

        src/main.cpp
        src/miniscript/Word.cpp
        src/miniscript/Word.h
)

target_include_directories(miniscript PRIVATE src)
