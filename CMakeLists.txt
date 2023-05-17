cmake_minimum_required(VERSION 3.24)
project(spot-palm)

set(CMAKE_CXX_STANDARD 17)

add_executable(spot-palm main.cpp util/tools.h user.h spots.h command_parser.h util/const_value.h spots.cpp user.cpp global_status.cpp)
#add_executable(spot_palm test.cpp)
