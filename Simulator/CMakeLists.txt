cmake_minimum_required(VERSION 2.6)
project(simulator)

#add_executable(opcodefunc opcodefunc.c)
#target_link_libraries(opcodefunc m)
#add_executable(opcodefunc opcodefunc.c)

add_executable(simulator simulator.c opcodefunc.c)
target_link_libraries(simulator m)

install(TARGETS simulator RUNTIME DESTINATION bin)
