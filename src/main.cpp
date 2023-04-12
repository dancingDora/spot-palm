#include <iostream>
#include <fstream>
#include "command_parser.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

CommandParser spot_palm;

int main() {
    freopen("case_test.txt", "r", stdin);
    freopen("case_test_res.txt", "w", stdout);
    string commandLine, result;

    while(std::getline(cin , commandLine)) {
        result = spot_palm.run(commandLine);
        if(result.length()) {
            if(result == "bye") {
                cout << "\033[36mbye bye ~\033[0m\n";
                break;
            }
            cout << result;
        }
    }
    return 0;
}
//cmake_minimum_required(VERSION 3.24)
//project()
//
//set(CMAKE_CXX_STANDARD 17)
//
//add_executable(main.cpp tools.h user.h spots.h)
