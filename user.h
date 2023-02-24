//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "tools.h"

class USER {
private:
    Char<16> password;
protected:
    const Char<16> uid;
public:
    Char<32> userName;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
    USER(int p) : privilege(p) {};

    USER() : password(), uid(), userName(), privilege(), gender(0) {};

    USER(const USER &usr) : uid(usr.uid), privilege(usr.privilege) {
        password = usr.password;
        userName = usr.userName;
        gender = usr.gender;
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

#endif //旅游景点模糊推荐_USER_H
