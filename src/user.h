//
// Created by 陆逸凡 on 2023/2/17.
//
#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "util/tools.h"
#include "spots.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>

using std::cerr;
using std::string;
using std::cout;
using std::vector;
using std::ostream;

class SpotManager;
class UserManager;
class Character{
public:
    ZODIAC_SIGNS starSeat;
    HOBBIES hobbies;
    Character();
};
class User{
private:
    Char<16> password;
public:
    Char<64> mailAddress;
    Char<32> userName;
    const unsigned uid;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
    Character character;

    vector<unsigned> historyComments; // history written commentsMap;

    //Now it is a lists show followers and follows.
    vector<unsigned> followerList;
    vector<unsigned> followList;

    bool privacy;
    //tmp list
    vector<unsigned> recommendUIDList_G; // recommend according to user Graph;
    vector<unsigned> recommendUIDList_S; // recommend according to user Spot browse history;

    User();

    User(const User &user);

    User(const unsigned &uid, const int &privilege, const int &gender,
         const string &userName, const string &mailAddress,
         const string &password);
    //获得该用户密码(private),仅限登陆(function : UserManager login(u, p))期间使用

    string getPassWord() const;

    friend bool operator == (const User &l, const User &r) {return l.userName == r.userName && l.uid == r.uid;}
    friend bool operator < (const User &l, const User &r) {return l.uid < r.uid;}
    friend bool operator > (const User &l, const User &r) {return l.uid > r.uid;}
    friend bool operator <= (const User &l, const User &r) {return l.uid <= r.uid;}
    friend bool operator >= (const User &l, const User &r) {return l.uid >= r.uid;}
    friend bool operator != (const User &l, const User &r) {return l.uid != r.uid;}

    friend ostream &operator << (ostream &uout, const User &u);
};

std::unordered_map<unsigned, int> loginUser;
class UserManager{
public:
    std::unordered_map<unsigned, User> users;
public:
    UserManager();
    //bool addUser(... user.enum) return true : false
    ~UserManager() {clear();}
    bool addUser(const std::string &user_name, const int &privilege,
                 const int &gender, const std::string &mail_address,
                 const unsigned &uid, const string &pass_word);

    //bool addUser(user) return true : false
    bool addUser(const User &u);

    //bool login(u, p) return true : false
    bool login(const unsigned &u, const string &p);

    //bool logout(u, p) return true : false
    bool logout(const unsigned &u);

    bool queryProfile(const unsigned &u, const unsigned &q);

    //最后一个参数num思路来源于修改文件权限：777 之类
    //每一个参数对应某一位数字：gender + 1， mail + 2， name + 4
    //根据输入的参数种类来确定修改资料种类
    bool modifyProfile(const unsigned &u, const int &gender, const string &mail,
                       const string &name, int num);

    bool clear();

    bool modifyGraph(const unsigned &u, unsigned modify_cond);

    bool queryGraph(unsigned &u, unsigned &q);

    bool recommendGraph(const unsigned &u);

    //usage for debug
    void checkRecommend (const unsigned &u);

    //Add Comments  : u(user id) -> s(spot id) : c(string comment)
    bool addComments(const unsigned &u, const unsigned &s, const string &c, SpotManager &spotManager);

    //Like Comments : u(user id) -> s(spot id) : c(like commentsMap[c])
    bool likeComments(const unsigned &u, const unsigned &s, const unsigned &c, SpotManager &spotManager);

    bool followUsers(const unsigned &u, const unsigned &q);

    bool modifyPrivacy(const unsigned &u, const bool &adjust);
};

#endif //旅游景点模糊推荐_USER_H