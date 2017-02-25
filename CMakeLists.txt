cmake_minimum_required(VERSION 2.6)
project(assembler)

add_executable(assembler main.cpp)

install(TARGETS assembler RUNTIME DESTINATION bin)
