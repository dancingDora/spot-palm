//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "tools.h"
#include <unordered_map>
class UserManager;
class USER {
private:
    Char<16> password;
public:
    Char<32> userName;
    const Char<16> uid;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
    USER(int p) : privilege(p) {};

    USER() : password(), uid(), userName(), privilege(), gender(0) {};

    USER(const USER &usr) : uid(usr.uid), privilege(usr.privilege) {
        password = usr.password;
        userName = usr.userName;
        gender = usr.gender;
    }
    friend bool operator == (const USER &l, const USER &r) {
        return l.userName == r.userName && l.uid == r.uid;
    }
    friend bool operator < (const USER &l, const USER &r) {

    }
};

class leader : public USER {
public:
    leader() : USER(7) {};
};

class contributor : public USER {
public:
    contributor() : USER(3) {

    };
};

class visitor : public USER {
public:
    visitor() : USER(0) {

    };
};

class user : public USER { ;
public:
    user() : USER(1) {

    }
};

class UserManager {

};


#endif //旅游景点模糊推荐_USER_H
