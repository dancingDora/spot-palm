//
// Created by 陆逸凡 on 2023/2/17.
//
#ifndef 旅游景点模糊推荐_USER_H
#define 旅游景点模糊推荐_USER_H

#include "tools.h"
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
class character{
public:
    ZODIAC_SIGNS starSeat;
    HOBBIES hobbies;
};
class USER{
private:
    Char<16> password;
public:
    Char<64> mailAddress;
    Char<32> userName;
    const unsigned uid;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
    character ch;

    vector<unsigned> historyComments; // history written comments;

    vector<unsigned> friendList; // friends list of uid

    bool sos;
    //tmp list
    vector<unsigned> recommendUIDList_G; // recommend according to user Graph;
    vector<unsigned> recommendUIDList_S; // recommend according to user Spot browse history;

    USER() : password(), uid(0), userName(), privilege(), gender(0) {
        sos = false;
    };

    USER(const USER &usr) : uid(usr.uid), privilege(usr.privilege) {
        password = usr.password;
        userName = usr.userName;
        gender = usr.gender;
        sos = usr.sos;
    }

    USER(const unsigned &uid, const int &privilege, const int &gender,
         const string &userName, const string &mailAddress,
         const string &password) : uid(uid),privilege(privilege) {
        this->gender = gender;
        this->userName = userName;
        this->mailAddress = mailAddress;
        this->password = password;
        sos = false;
    }
    //获得该用户密码(private),仅限登陆(function : UserManager login(u, p))期间使用
    string getPassWord() const {
        return this->password;
    }

    friend bool operator == (const USER &l, const USER &r) {return l.userName == r.userName && l.uid == r.uid;}
    friend bool operator < (const USER &l, const USER &r) {return l.uid < r.uid;}
    friend bool operator > (const USER &l, const USER &r) {return l.uid > r.uid;}
    friend bool operator <= (const USER &l, const USER &r) {return l.uid <= r.uid;}
    friend bool operator >= (const USER &l, const USER &r) {return l.uid >= r.uid;}
    friend bool operator != (const USER &l, const USER &r) {return l.uid != r.uid;}

    friend ostream &operator << (ostream &uout, const USER &u) {
        uout << "uid :          " << u.uid << '\n';
        uout << "user name :    " << u.userName << '\n';
        uout << "mail address : " << u.mailAddress << '\n';
        uout << "gender :       " << u.gender << '\n';
        uout << "privilege :    " << u.privilege << '\n';
        return uout;
    }
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
            return true;
        }
        else cerr << "[UserManager AddUser] Invalid add : "  << uid << " add the same uid.\n";
        return false;
    }
    //bool addUser(user) return true : false
    bool addUser(const USER &u) {
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
        auto iterPrvl = users.find(u);
        if(iterPrvl->second.privilege <= iter->second.privilege) {
            cerr << "[UserManager queryProfile] You do not have enough privileges to find user : " << iter->second.uid << '\n';
            return false;
        }
        cout << "uid :          " << q << '\n';
        cout << "user name :    " << iter->second.userName << '\n';
        cout << "mail address : " << iter->second.mailAddress << '\n';
        cout << "gender :       " << iter->second.gender << '\n';
        cout << "privilege :    " << iter->second.privilege << '\n';
        return true;
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

    bool modifyGraph(const unsigned &u,
                     const unsigned modify_cond) {
        if(loginUser.find(u) == loginUser.cend()) {
            cerr << "[UserManager modifyGraph] Invalid modifyGraph : " << u << " not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager modifyGraph] Invalid modifyGraph : " << u << " not exist.\n";
            return false;
        }
        //if(MODIFY) : this->users[u].ch.hobbies.xxx = xxx
        if((modify_cond & 0x0000001l) == 0x0000001l)this->users[u].ch.hobbies.swim = true;
        if((modify_cond & 0x0000002l) == 0x0000002l)this->users[u].ch.hobbies.run = true;
        if((modify_cond & 0x0000004l) == 0x0000004l)this->users[u].ch.hobbies.cycle = true;
        if((modify_cond & 0x0000008l) == 0x0000008l)this->users[u].ch.hobbies.basketball = true;
        if((modify_cond & 0x0000010l) == 0x0000010l)this->users[u].ch.hobbies.football = true;
        if((modify_cond & 0x0000020l) == 0x0000020l)this->users[u].ch.hobbies.tennis = true;
        if((modify_cond & 0x0000040l) == 0x0000040l)this->users[u].ch.hobbies.table_tennis = true;
        if((modify_cond & 0x0000080l) == 0x0000080l)this->users[u].ch.hobbies.box = true;
        if((modify_cond & 0x0000100l) == 0x0000100l)this->users[u].ch.hobbies.shoot = true;
        if((modify_cond & 0x0000200l) == 0x0000200l)this->users[u].ch.hobbies.volleyball = true;
        if((modify_cond & 0x0000400l) == 0x0000400l)this->users[u].ch.hobbies.baseball = true;
        if((modify_cond & 0x0000800l) == 0x0000800l)this->users[u].ch.hobbies.gymnastic = true;
        if((modify_cond & 0x0001000l) == 0x0001000l)this->users[u].ch.hobbies.sky = true;
        if((modify_cond & 0x0002000l) == 0x0002000l)this->users[u].ch.hobbies.ice_skating = true;
        if((modify_cond & 0x0004000l) == 0x0004000l)this->users[u].ch.hobbies.marathon = true;
        if((modify_cond & 0x0008000l) == 0x0008000l)this->users[u].ch.hobbies.row = true;
        if((modify_cond & 0x0010000l) == 0x0010000l)this->users[u].ch.hobbies.surf = true;
        if((modify_cond & 0x0020000l) == 0x0020000l)this->users[u].ch.hobbies.classical = true;
        if((modify_cond & 0x0040000l) == 0x0040000l)this->users[u].ch.hobbies.jazz_blues = true;
        if((modify_cond & 0x0080000l) == 0x0080000l)this->users[u].ch.hobbies.folk = true;
        if((modify_cond & 0x0100000l) == 0x0100000l)this->users[u].ch.hobbies.pop = true;
        if((modify_cond & 0x0200000l) == 0x0200000l)this->users[u].ch.hobbies.rock = true;
        if((modify_cond & 0x0400000l) == 0x0400000l)this->users[u].ch.hobbies.dance = true;
        if((modify_cond & 0x0800000l) == 0x0800000l)this->users[u].ch.hobbies.rap = true;
        if((modify_cond & 0x1000000l) == 0x1000000l)this->users[u].ch.hobbies.electronic = true;
        return true;
    };

    bool queryGraph(unsigned &u, unsigned &q) {
        if(loginUser.find(u) == loginUser.cend()) {
            cerr << "[UserManager queryGraph] Invalid queryGraph : " << u << " not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager queryGraph] Invalid queryGraph : " << u << " not exist.\n";
            return false;
        }
        if(users.find(q) == users.cend()) {
            cerr << "[UserManager queryGraph] Invalid queryGraph : " << q << " not found.\n";
            return false;
        }

        {//输出表
        if(this->users[q].ch.hobbies.swim)cout << "swim\t";
        if(this->users[q].ch.hobbies.run)cout << "run\t";
        if(this->users[q].ch.hobbies.cycle)cout << "cycle\t";
        if(this->users[q].ch.hobbies.basketball)cout << "basketball\t";
        if(this->users[q].ch.hobbies.football)cout << "football\t";
        if(this->users[q].ch.hobbies.tennis)cout << "tennis\t";
        if(this->users[q].ch.hobbies.table_tennis)cout << "table_tennis\t";
        if(this->users[q].ch.hobbies.box)cout << "box\t";
        if(this->users[q].ch.hobbies.shoot)cout << "shoot\t";
        if(this->users[q].ch.hobbies.volleyball)cout << "volleyball\t";
        if(this->users[q].ch.hobbies.baseball)cout << "baseball\t";
        if(this->users[q].ch.hobbies.gymnastic)cout << "gymnastic\t";
        if(this->users[q].ch.hobbies.sky)cout << "sky\t";
        if(this->users[q].ch.hobbies.ice_skating)cout << "ice_skating\t";
        if(this->users[q].ch.hobbies.marathon)cout << "marathon\t";
        if(this->users[q].ch.hobbies.row)cout << "row\t";
        if(this->users[q].ch.hobbies.surf)cout << "surf";
        cout << '\n';
        if(this->users[q].ch.hobbies.classical)cout << "classical\t";
        if(this->users[q].ch.hobbies.jazz_blues)cout << "jazz_blues\t";
        if(this->users[q].ch.hobbies.folk)cout << "folk\t";
        if(this->users[q].ch.hobbies.pop)cout << "pop\t";
        if(this->users[q].ch.hobbies.rock)cout << "rock\t";
        if(this->users[q].ch.hobbies.dance)cout << "dance\t";
        if(this->users[q].ch.hobbies.rap)cout << "rap\t";
        if(this->users[q].ch.hobbies.electronic)cout << "electronic";
        cout << '\n';
        }
        return true;
    }

    bool recommendGraph(const unsigned &u) {
        //error handle
        if(loginUser.find(u) == loginUser.cend()) {
            cerr << "[UserManager recommendGraph] Invalid recommendGraph : " << u << " not login.\n";
            return false;
        }
        if(users.find(u) == users.cend()) {
            cerr << "[UserManager recommendGraph] Invalid recommendGraph : " << u << " not exist.\n";
            return false;
        }
        //initialize
        std::vector<unsigned> maxList;
        maxList.clear();
        this->users[u].recommendUIDList_G.clear();
        //algorithm : initialize tmp
        unsigned Max = 0;
        std::unordered_map<unsigned, std::vector<unsigned> > recommendList;
        recommendList.clear();
        //algorithm : calculate recommendList
        int cnt = 0;
        for(auto it : users) {
            Max = std::max(Max,users[u].ch.hobbies.getDifference(users[it.first].ch.hobbies));
            recommendList[users[u].ch.hobbies.getDifference(users[it.first].ch.hobbies)].push_back(it.second.uid);
        }
        for(int i = Max; i > 0; i--) {
            if(recommendList[i].empty()) continue;
            this->users[u].recommendUIDList_G.insert(this->users[u].recommendUIDList_G.end(), recommendList[i].begin(), recommendList[i].end());
        }
        return true;
    }

    //usage for debug
    void checkRecommend (const unsigned &u) {
        if(users.find(u) == users.cend()) {
            cerr << u << " not found.\n";
            return;
        }
        for(auto it : users[u].recommendUIDList_G)
            cout << users[it] << std::endl;
        cout << "Recommend success : End of check RecommendUIDList_G.\n";
        return;
    }

    //Add Comments : u(user id) -> s(spot id) : c(put comments)
    bool addComments(const unsigned &u, const unsigned &s, const string &c){

    };

    //Like Comments : u(user id) -> s(spot id) : c(like comments[c])
    bool likeComments(const unsigned &u, const unsigned &s, const unsigned &c) {};


};

#endif //旅游景点模糊推荐_USER_H