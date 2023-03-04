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
using std::cout;
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
    UserManager() {users.clear();}
    //bool addUser(... user.enum) return true : false
    ~UserManager() {clear();}
    bool addUser(const std::string &user_name, const int &privilege,
                 const int &gender, const std::string &mail_address,
                 const unsigned &uid, const string &pass_word){
        if(users.find(uid) == users.end()) {
            USER *newMember = new USER(uid, privilege, gender, user_name, mail_address, pass_word);
            users.insert(std::pair<unsigned, USER>(uid, *newMember));
            delete newMember;
        }
        else cerr << "[UserManager AddUser] Invalid add : "  << uid << " add the same uid.\n";
        return false;
    }
    //bool addUser(user) return true : false
    bool addUser(const user &u) {
        if(users.find(u.uid) == users.end())
            users.insert(std::pair<unsigned, USER>(u.uid, u));
        else cerr << "[UserManager AddUser] Invalid add : " << u.uid << " add the same uid.\n";
        return false;
    }
    //bool login(u, p) return true : false
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
    //bool logout(u, p) return true : false
    bool logout(const unsigned &u) {
        auto it = loginUser.find(u);
        if(it == loginUser.cend()) {
            cerr << "[UserManager AddUser] Invalid logout : " << u << " has not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager AddUser] Invalid logout : " << u << " not found.\n";
            return false;
        }
        loginUser.erase(it);
        return true;
    }

    bool queryProfile(const unsigned &u, const unsigned &q) {
        if(loginUser.find(u) == loginUser.cend()) {
            cerr << "[UserManager queryProfile] Invalid queryProfile : " << u << " not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager queryProfile] Invalid queryProfile : " << u << " not exist.\n";
            return false;
        }
        if(users.find(q) == users.cend()) {
            cerr << "[UserManager queryProfile] Invalid queryProfile : " << q << " not found.\n";
            return false;
        }
        auto iter = users.find(q);
        cout << "uid : " << q << '\n';
        cout << "user name : " << iter->second.userName << '\n';
        cout << "gender : " << iter->second.gender << '\n';
        cout << "privilege : " << iter->second.privilege << '\n';
        return 1;
    }

    //最后一个参数num思路来源于修改文件权限：777 之类
    //每一个参数对应某一位数字：gender + 1， mail + 2， name + 4
    //根据输入的参数种类来确定修改资料种类
    bool modifyProfile(const unsigned &u, const int &gender, const string &mail,
                       const string &name, int num = 0) {
        if(num >= 8) {
            cerr << "[UserManager modifyProfile] Invalid test_cond : without Xor.\n";
            cerr << "Maybe because of without valid uid input. uid : " << u << '\n';
        }
        if(loginUser.find(u) == loginUser.cend()) {
            cerr << "[UserManager modifyProfile] Invalid modifyProfile : " << u << " not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager modifyProfile] Invalid modifyProfile : " << u << " not exist.\n";
            return false;
        }
        if(num & 0b100l) users[u].userName = name;
        if(num & 0b10l) users[u].mailAddress = mail;
        if(num & 0b1l) users[u].gender = gender;
        return true;
    }

    bool clear() {
        users.clear();
        loginUser.clear();
        return true;
    }
    //TODO: extend here
};

#endif //旅游景点模糊推荐_USER_H