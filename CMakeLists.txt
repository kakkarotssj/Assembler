cmake_minimum_required(VERSION 2.6)
project(assembler)

add_executable(assembler main.c lexer.c tokenstream.c opcodestream.c)

install(TARGETS assembler RUNTIME DESTINATION bin)
