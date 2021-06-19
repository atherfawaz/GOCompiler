# cmake_minimum_required(VERSION <specify CMake version here>)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp Lexer.h Token.h Token.cpp Lexer.cpp globals.h Parser.cpp Parser.h global_path.h Assembler.cpp Assembler.h Quadruple.cpp Quadruple.h Tac-Mac.h Tac-Mac.cpp)