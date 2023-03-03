//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "tools.h"
#include <unordered_map>
#include <iostream>
using std::cerr;
using std::string;
class UserManager;
class USER{
private:
    Char<16> password;
public:
    Char<64> mailAddress;
    Char<32> userName;
    const unsigned uid;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
    USER(int p) : privilege(p), uid(0) {};

    USER() : password(), uid(0), userName(), privilege(), gender(0) {};

    USER(const USER &usr) : uid(usr.uid), privilege(usr.privilege) {
        password = usr.password;
        userName = usr.userName;
        gender = usr.gender;
    }

    USER(const unsigned &uid, const int &privilege, const int &gender,
         const string &userName, const string &mailAddress,
         const string &password) : uid(uid),privilege(privilege) {
        this->gender = gender;
        this->userName = userName;
        this->mailAddress = mailAddress;
        this->password = password;
    }
    //获得该用户密码(private),仅限登陆(function : UserManager login(u, p))期间使用
    string getPassWord() const {
        return this->password;
    }

    friend bool operator == (const USER &l, const USER &r) {
        return l.userName == r.userName && l.uid == r.uid;
    }

    friend bool operator < (const USER &l, const USER &r) {
        return l.uid < r.uid;
    }

};

class leader : public USER {
public:
    leader() : USER(7) {};
};

class contributor : public USER {
public:
    contributor() : USER(3) {};
};

class visitor : public USER {
public:
    visitor() : USER(0) {};
};

class user : public USER {
public:
    user() : USER(1) {};
};

std::unordered_map<unsigned, int> loginUser;
class UserManager{
public:
    std::unordered_map<unsigned, USER> users;
public:
    UserManager() {users.clear();};
    bool addUser(const std::string &user_name, const int &privilege,
                 const int &gender, const std::string &mail_address,
                 const unsigned &uid, const string &pass_word){
        if(users.find(uid) == users.end()) {
            USER *newMember = new USER(uid, privilege, gender, user_name, mail_address, pass_word);
            users.insert(std::pair<unsigned, USER>(uid, *newMember));
            delete newMember;
        }
        else cerr << "[UserManager AddUser] Invalid add : add the same uid.\n";
        return false;
    }

    bool login(const unsigned &u, const string &p) {
        if(loginUser.find(u) != loginUser.cend()) {
            cerr << "[UserManager AddUser] Invalid login : " << u << " has login\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager AddUser] Invalid login : " << u << " not found.\n";
            return false;
        }
        if(p != users[u].getPassWord()) {
            cerr << "[UserManager AddUser] Invalid login : " << u << " input the wrong password.\n";
            return false;
        }
        loginUser.insert(std::pair<unsigned, unsigned>(u, users[u].privilege));
        return true;
    }

    bool logout(const string &u) {
        return loginUser.erase();
    }


};


#endif //旅游景点模糊推荐_USER_H
