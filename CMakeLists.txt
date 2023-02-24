cmake_minimum_required(VERSION 3.24)
project(spot-palm)

set(CMAKE_CXX_STANDARD 17)

add_executable(spot-palm main.cpp tools.h user.h)