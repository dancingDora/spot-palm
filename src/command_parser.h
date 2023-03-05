//
// Created by 陆逸凡 on 2023/3/3.
//

#ifndef SPOT_PALM_COMMAND_PARSER_H
#define SPOT_PALM_COMMAND_PARSER_H

#include <iostream>
#include "spot.h"
#include "user.h"

using std::string;
using std::cerr;
using std::cout;
using std::stoi;
using std::stod;

class CommandParser {
    UserManager users;
    SpotManager spots;
public:
    string run(const string &t) {
        TokenScanner token(t);
        string key = token.NextToken();
        if (!key.length()) {
            cerr << "[CommandParser run] Invalid input, key.length() = 0.\n";
            return "";
        }
        if (key == "exit") return parseExit();
        //clear : please input root password
        else if(key == "clear") return parseClear(token);
        else if (key == "add_user") return parseAddUser(token);
        else if (key == "login") return parseLogin(token);
        else if (key == "logout") return parseLogout(token);
        else if (key == "query_profile") return parseQueryProfile(token);
        else if (key == "modify_profile") return parseModifyProfile(token);
        else if (key == "add_spot") return parseAddSpot(token);
        else if (key == "--help") return parseHelp();
        else {
            cerr << "[CommandParser run] Invalid key, command not found.\n";
            cout << "If you don`t know how to use spot-palm for command line,\n";
            cout << "You can try to input `--help`.\n";
            return "";
        }
    }

    //bool addUser(const std::string &user_name, const int &privilege,
    //                 const int &gender, const std::string &mail_address,
    //                 const unsigned &uid, const string &pass_word)
    string parseAddUser(TokenScanner &token) {
        string key = token.NextToken();
        string n;//user_name
        string m;//mail_address
        string p;//pass_word

        int v, g;//privilege, gender
        unsigned i;//uid

        //规定
        //-n : user_name
        //-v : privilege
        //-g : gender
        //-m : mail_address
        //-i : uid
        //-p : pass_word
        unsigned test_cond = 0;
        while (!key.empty()) {
            if (key == "-n") {
                n = token.NextToken();
                test_cond |= 0b1l;
            } else if (key == "-v") {
                v = stoi(token.NextToken());
                test_cond |= 0b10l;
            } else if (key == "-g") {
                g = stoi(token.NextToken());
                test_cond |= 0b100l;
            } else if (key == "-m") {
                m = token.NextToken();
                test_cond |= 0b1000l;
            } else if (key == "-i") {
                i = stoi(token.NextToken());
                test_cond |= 0b10000l;
            } else if (key == "-p") {
                p = token.NextToken();
                test_cond |= 0b100000l;
            } else {
                cerr << "[CommandParser parseAddUser] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {// test the parameter is completed
            if ((test_cond & 0b111111l) != test_cond) {
                cerr << "[CommandParser parseAddUser] the parameter is not completed.\n";
                return "[CommandParser parseAddUser] the parameter is not completed.\n";
            }
        };
        return users.addUser(n, v, g, m, i, p)
               ? "\033[36mAdd user success.\033[0m\n" : "AddUser failed.\n";
    };

    //    bool login(const unsigned &u, const string &p)
    string parseLogin(TokenScanner &token) {
        string key = token.NextToken();
        string p; // password
        unsigned i; // uid
        // -i : uid
        // -p : password
        unsigned test_cond = 0;
        while (!key.empty()) {
            if (key == "-i") {
                i = stoi(token.NextToken());
                test_cond |= 0b1l;
            } else if (key == "-p") {
                p = token.NextToken();
                test_cond |= 0b10l;
            } else {
                cerr << "[CommandParser parseLogin] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {// test the parameter is completed
            if (test_cond != 0b11l) {
                cerr << "[CommandParser parseLogin] the parameter is not completed.\n";
                return "[CommandParser parseLogin] the parameter is not completed.\n";
            }
        };
        return users.login(i, p)
               ?  "\033[33mLogin success.\033[0m\n" : "Login failed.\n";
    }

    //    bool logout(const unsigned &u)
    string parseLogout(TokenScanner &token) {
        string key = token.NextToken();
        unsigned i = 0;
        // -i : uid
        while (!key.empty()) {
            if (key == "-i") i = stoi(token.NextToken());
            else {
                cerr << "[CommandParser parseLogout] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {// test the parameter is completed
            if (i == 0) {
                cerr << "[CommandParser parseLogin] the parameter is not completed.\n";
                return "[CommandParser parseLogin] the parameter is not completed.\n";
            }
        }
        return users.logout(i)
               ? "\033[36mLogout success.\033[0m\n" : "Logout failed.\n";
    }

    //    bool queryProfile(const unsigned &u, const unsigned &q)
    string parseQueryProfile(TokenScanner &token) {
        string key = token.NextToken();
        unsigned i;
        unsigned q;
        // -i : uid
        // -q : query->uid
        unsigned test_cond = 0;
        while(!key.empty()) {
            if(key == "-i") {
                i = stoi(token.NextToken());
                test_cond |= 0b1l;
                //cout << "-i read success : " << i << std::endl; //output debug
            }
            else if(key == "-q") {
                q = stoi(token.NextToken());
                test_cond |= 0b10l;
                //cout << "-q read success : " << q << std::endl;//output debug
            }
            else {
                cerr << "[CommandParser parseQueryProfile] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {// test the parameter is completed
            if (test_cond != 0b11l) {
                cerr << "[CommandParser parseQueryProfile] the parameter is not completed.\n";
                return "[CommandParser parseQueryProfile] the parameter is not completed.\n";
            }
        }
        return users.queryProfile(i, q) ? "\033[36mQuery profile success.\033[0m\n" : "QueryProfile failed.\n";
    }

    //bool modifyProfile(const unsigned &u, const int &gender, const string &mail,
    //                       const string &name, int num = 0)
    string parseModifyProfile(TokenScanner &token) {
        string key = token.NextToken();
        unsigned i;
        int g;
        string m, n;
        unsigned test_cond = 0;

        // -i : uid
        // -g : gender
        // -m : mail_address
        // -n : name
        // test_cond : gender + 1， mail + 2， name + 4
        while(!key.empty()) {
            if(key == "-i") {
                i = stoi(token.NextToken());
                test_cond |= 0b1000l;
            }
            else if(key == "-g") {
                g = stoi(token.NextToken());
                test_cond |= 0b1l;
            }
            else if(key == "-m") {
                m = token.NextToken();
                test_cond |= 0b10l;
            }
            else if(key == "-n") {
                n = token.NextToken();
                test_cond |= 0b100l;
            }
            else {
                cerr << "[CommandParser parseModifyProfile] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {//judge is uid input
            test_cond ^= 0b1000l;
            if((test_cond & 0b1000l) == 0b1000l) {
                cerr << "[CommandParser parseModifyProfile] the parameter is not completed without uid.\n";
                return "[CommandParser parseModifyProfile] the parameter is not completed without uid.\n";
            }
        }
        return users.modifyProfile(i,g,m,n,test_cond)
        ? "\033[33mModify Profile success.\033[0m\n" : "Modify Profile failed.\n";

    }
    //bool addSpot(const string &spotNameA, const int &sidA,
    //                 const double &t, const double &v, const double &h, const double &c, const double &d,
    //                 const PROVINCE &provinceA, const string &cityA,
    //                 const double & NSA, const double & WEA)
    string parseAddSpot(TokenScanner &token) {
        string key = token.NextToken();
        string n;
        int i;
        double t,v,h,c,d;
        PROVINCE p;
        string s;
        double ns, we;

        // -n : spotName
        // -i : sid
        // -t : status temperature
        // -v : status visitorAmount
        // -h : status humidity
        // -c : status consumption
        // -d : status distance

        // -p : province
        // -s : city
        // -ns : NS
        // -we : WE
        unsigned test_cond = 0;
        while(!key.empty()) {
            if(key == "-n") {}
            else if(key == "-i") {
                i = stoi(token.NextToken());
                test_cond |= 0b1l;
            }
            else if(key == "-t") {
                t = stod(token.NextToken());
                test_cond |= 0b10l;
            }
            else if(key == "-v") {
                v = stod(token.NextToken());
                test_cond |= 0b100l;
            }
            else if(key == "-h") {
                h = stod(token.NextToken());
                test_cond |= 0b1000l;
            }
            else if(key == "-c") {
                c = stod(token.NextToken());
                test_cond |= 0b10000l;
            }
            else if(key == "-d") {
                d = stod(token.NextToken());
                test_cond |= 0b100000l;
            }
            else if(key == "-p") {
                p = sToProv(token.NextToken());
                test_cond |= 0b1000000l;
            }
            else if(key == "-s") {
                s = token.NextToken();
                test_cond |= 0b10000000l;
            }
            else if(key == "-NS") {
                ns = stod(token.NextToken());
                test_cond |= 0b100000000l;
            }
            else if(key == "-WE") {
                we = stod(token.NextToken());
                test_cond |= 0b1000000000l;
            }
            else {
                cerr << "[CommandParser parseAddSpot] wrong input / not such command.\n";
            }
            key = token.NextToken();
        }
        {//test the parameter is completed
            if(test_cond != 0b1111111111l) {
                cerr << "[CommandParser parseAddSpot] the parameter is not completed.\n";
                return "[CommandParser parseAddSpot] the parameter is not completed.\n";
            }
        }
        return spots.addSpot(n,i,t,v,h,c,d,p,s,ns,we)
        ? "\033[33mAdd Spot success.\033[0m\n" : "AddSpot parse failed.\n";
    }
    string parseClear(TokenScanner &token) {
        string key = token.NextToken();
        if(key != "dsqcxtwjhlyf") {
            return "clear failed.\n";
        }
        users.clear();
        spots.clear();
        return "clear success!\n";
    }
    string parseHelp() {
        return help() ? "parse help failed" : "\033[36mYou`re welcome.\033[0m\n";
    }
    string parseExit() {
        return "bye";
    }
};

#endif //SPOT_PALM_COMMAND_PARSER_H
