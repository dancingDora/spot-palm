cmake_minimum_required(VERSION 3.24)
project(spot-palm)

set(CMAKE_CXX_STANDARD 17)

#add_executable(spot-palm main.cpp tools.h user.h spot.h command_parser.h const_value.h )
add_executable(spot_palm test.cpp)