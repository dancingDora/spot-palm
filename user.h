//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "char.h"

class USER{
private:
    Char<16> password;
protected:
    const Char<16> uid;
public:
    Char<32> userName;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.

    virtual USER():password(1),uid(1),userName(1),privilege(1), gender(0){};
    virtual USER(const USER &usr):uid(usr.uid), privilege(usr.privilege){
        password = usr.password;
        userName = usr.userName;
        gender = usr.gender;
    }
};

class leader : public USER {
    leader()
};

class contributor : public USER {

};

class visitor : public USER {

};

class user : public USER {

};
#endif //旅游景点模糊推荐_USER_H
