#include <iostream>
#include "tools.h"
#include "user.h"
#include "spot.h"
#include <stdlib.h>
#include "status.h"
using std::cout;
using std::endl;
int main() {
    UserManager test;
    user xiaoming;
    std::cout << xiaoming.privilege << std::endl;
    test.addUser("xiaoming", 1, 1, "sjtu.edu.cn", 123, "123");
    std::cout << test.users[123].privilege << endl;

}
//cmake_minimum_required(VERSION 3.24)
//project()
//
//set(CMAKE_CXX_STANDARD 17)
//
//add_executable(main.cpp tools.h user.h)
