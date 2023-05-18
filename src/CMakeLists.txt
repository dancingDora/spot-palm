cmake_minimum_required(VERSION 3.24)
project(spot-palm)

set(CMAKE_CXX_STANDARD 17)

add_executable(spot-palm main.cpp user.cpp spots.cpp global_status.cpp tools.cpp)
#add_executable(test test.cpp tools.cpp)
