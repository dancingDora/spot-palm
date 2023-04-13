//
// Created by 陆逸凡 on 2023/3/16.
//

#include "user.h"

Character::Character() {
    hobbies = *new HOBBIES();
    starSeat = Pisces;
}

User::User(): password(), uid(0), userName(), privilege(), gender(0) {
    privacy = false;
};

User::User(const User &user) : uid(user.uid), privilege(user.privilege) {
    password = user.password;
    userName = user.userName;
    gender = user.gender;
    privacy = user.privacy;
}

User::User(const unsigned &uid, const int &privilege, const int &gender,
     const string &userName, const string &mailAddress,
     const string &password) : uid(uid),privilege(privilege) {
    this->gender = gender;
    this->userName = userName;
    this->mailAddress = mailAddress;
    this->password = password;
    privacy = false;
}

string User::getPassWord() const {
    return this->password;
}

ostream &operator << (ostream &uout, const User &u) {
    uout << "uid :          " << u.uid << '\n';
    uout << "user name :    " << u.userName << '\n';
    uout << "mail address : " << u.mailAddress << '\n';
    uout << "gender :       " << u.gender << '\n';
    uout << "privilege :    " << u.privilege << '\n';
    return uout;
}

UserManager::UserManager() {
    users.clear();
}

bool UserManager::addUser(const std::string &user_name, const int &privilege,
             const int &gender, const std::string &mail_address,
             const unsigned &uid, const string &pass_word){
    if(users.find(uid) == users.end()) {
        User *newMember = new User(uid, privilege, gender, user_name, mail_address, pass_word);
        users.insert(std::pair<unsigned, User>(uid, *newMember));
        delete newMember;
        return true;
    }
    else cerr << "[UserManager AddUser] Invalid add : "  << uid << " add the same uid.\n";
    return false;
}

bool UserManager::addUser(const User &u) {
    if(users.find(u.uid) == users.end())
        users.insert(std::pair<unsigned, User>(u.uid, u));
    else cerr << "[UserManager AddUser] Invalid add : " << u.uid << " add the same uid.\n";
    return false;
}

bool UserManager::login(const unsigned &u, const string &p) {
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

bool UserManager::logout(const unsigned &u) {
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

bool UserManager::queryProfile(const unsigned &u, const unsigned &q) {
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

bool UserManager::modifyProfile(const unsigned &u, const int &gender, const string &mail,
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

bool UserManager::clear() {
    users.clear();
    loginUser.clear();
    return true;
}

bool UserManager::modifyGraph(const unsigned &u, unsigned modify_cond) {
    if(loginUser.find(u) == loginUser.cend()) {
        cerr << "[UserManager modifyGraph] Invalid modifyGraph : " << u << " not login.\n";
        return false;
    }
    if(users.find(u) == users.cend()) {
        cerr << "[UserManager modifyGraph] Invalid modifyGraph : " << u << " not exist.\n";
        return false;
    }
    //if(MODIFY) : this->users[u].character.hobbies.xxx = xxx
    if((modify_cond & 0x0000001l) == 0x0000001l)this->users[u].character.hobbies.swim = true;
    if((modify_cond & 0x0000002l) == 0x0000002l)this->users[u].character.hobbies.run = true;
    if((modify_cond & 0x0000004l) == 0x0000004l)this->users[u].character.hobbies.cycle = true;
    if((modify_cond & 0x0000008l) == 0x0000008l)this->users[u].character.hobbies.basketball = true;
    if((modify_cond & 0x0000010l) == 0x0000010l)this->users[u].character.hobbies.football = true;
    if((modify_cond & 0x0000020l) == 0x0000020l)this->users[u].character.hobbies.tennis = true;
    if((modify_cond & 0x0000040l) == 0x0000040l)this->users[u].character.hobbies.table_tennis = true;
    if((modify_cond & 0x0000080l) == 0x0000080l)this->users[u].character.hobbies.box = true;
    if((modify_cond & 0x0000100l) == 0x0000100l)this->users[u].character.hobbies.shoot = true;
    if((modify_cond & 0x0000200l) == 0x0000200l)this->users[u].character.hobbies.volleyball = true;
    if((modify_cond & 0x0000400l) == 0x0000400l)this->users[u].character.hobbies.baseball = true;
    if((modify_cond & 0x0000800l) == 0x0000800l)this->users[u].character.hobbies.gymnastic = true;
    if((modify_cond & 0x0001000l) == 0x0001000l)this->users[u].character.hobbies.sky = true;
    if((modify_cond & 0x0002000l) == 0x0002000l)this->users[u].character.hobbies.ice_skating = true;
    if((modify_cond & 0x0004000l) == 0x0004000l)this->users[u].character.hobbies.marathon = true;
    if((modify_cond & 0x0008000l) == 0x0008000l)this->users[u].character.hobbies.row = true;
    if((modify_cond & 0x0010000l) == 0x0010000l)this->users[u].character.hobbies.surf = true;
    if((modify_cond & 0x0020000l) == 0x0020000l)this->users[u].character.hobbies.classical = true;
    if((modify_cond & 0x0040000l) == 0x0040000l)this->users[u].character.hobbies.jazz_blues = true;
    if((modify_cond & 0x0080000l) == 0x0080000l)this->users[u].character.hobbies.folk = true;
    if((modify_cond & 0x0100000l) == 0x0100000l)this->users[u].character.hobbies.pop = true;
    if((modify_cond & 0x0200000l) == 0x0200000l)this->users[u].character.hobbies.rock = true;
    if((modify_cond & 0x0400000l) == 0x0400000l)this->users[u].character.hobbies.dance = true;
    if((modify_cond & 0x0800000l) == 0x0800000l)this->users[u].character.hobbies.rap = true;
    if((modify_cond & 0x1000000l) == 0x1000000l)this->users[u].character.hobbies.electronic = true;
    return true;
}

bool UserManager::queryGraph(unsigned &u, unsigned &q) {
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
        if(this->users[q].character.hobbies.swim)cout << "swim\t";
        if(this->users[q].character.hobbies.run)cout << "run\t";
        if(this->users[q].character.hobbies.cycle)cout << "cycle\t";
        if(this->users[q].character.hobbies.basketball)cout << "basketball\t";
        if(this->users[q].character.hobbies.football)cout << "football\t";
        if(this->users[q].character.hobbies.tennis)cout << "tennis\t";
        if(this->users[q].character.hobbies.table_tennis)cout << "table_tennis\t";
        if(this->users[q].character.hobbies.box)cout << "box\t";
        if(this->users[q].character.hobbies.shoot)cout << "shoot\t";
        if(this->users[q].character.hobbies.volleyball)cout << "volleyball\t";
        if(this->users[q].character.hobbies.baseball)cout << "baseball\t";
        if(this->users[q].character.hobbies.gymnastic)cout << "gymnastic\t";
        if(this->users[q].character.hobbies.sky)cout << "sky\t";
        if(this->users[q].character.hobbies.ice_skating)cout << "ice_skating\t";
        if(this->users[q].character.hobbies.marathon)cout << "marathon\t";
        if(this->users[q].character.hobbies.row)cout << "row\t";
        if(this->users[q].character.hobbies.surf)cout << "surf";
        cout << '\n';
        if(this->users[q].character.hobbies.classical)cout << "classical\t";
        if(this->users[q].character.hobbies.jazz_blues)cout << "jazz_blues\t";
        if(this->users[q].character.hobbies.folk)cout << "folk\t";
        if(this->users[q].character.hobbies.pop)cout << "pop\t";
        if(this->users[q].character.hobbies.rock)cout << "rock\t";
        if(this->users[q].character.hobbies.dance)cout << "dance\t";
        if(this->users[q].character.hobbies.rap)cout << "rap\t";
        if(this->users[q].character.hobbies.electronic)cout << "electronic";
        cout << '\n';
    }
    return true;
}

bool UserManager::recommendGraph(const unsigned &u) {
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
        Max = std::max(Max,users[u].character.hobbies.getDifference(users[it.first].character.hobbies));
        recommendList[users[u].character.hobbies.getDifference(users[it.first].character.hobbies)].push_back(it.second.uid);
    }
    for(int i = Max; i > 0; i--) {
        if(recommendList[i].empty()) continue;
        this->users[u].recommendUIDList_G.insert(this->users[u].recommendUIDList_G.end(), recommendList[i].begin(), recommendList[i].end());
    }
    return true;
}

void UserManager::checkRecommend (const unsigned &u) {
    if(users.find(u) == users.cend()) {
        cerr << u << " not found.\n";
        return;
    }
    for(auto it : users[u].recommendUIDList_G)
        cout << users[it] << std::endl;
    cout << "Recommend success : End of check RecommendUIDList_G.\n";
    return;
}

bool UserManager::addComments(const unsigned &u, const unsigned &s, const string &c, SpotManager &spotManager) {
    //error handle
    if(loginUser.find(u) == loginUser.cend()) {
        cerr << "[UserManager addComments] Invalid addComments : " << u << " not login.\n";
        return false;
    }
    if(users.find(u) == users.cend()) {
        cerr << "[UserManager addComments] Invalid addComments : " << u << " not exist.\n";
        return false;
    }
    //execute
    unsigned res = hashUS(u, s);
    users[u].historyComments.push_back(res);
    return spotManager.putComment(s, u, res,c);
}

bool UserManager::likeComments(const unsigned &u, const unsigned &s, const unsigned &c, SpotManager &spotManager) {
    //error handle
    if(loginUser.find(u) == loginUser.cend()) {
        cerr << "[UserManager likeComments] Invalid likeComments : " << u << " not login.\n";
        return false;
    }
    if(users.find(u) == users.cend()) {
        cerr << "[UserManager likeComments] Invalid likeComments : " << u << " not exist.\n";
        return false;
    }
    //execute
    unsigned res = hashUS(u, s);
    return spotManager.putCommentLike(s, u, res);
};

bool UserManager::followUsers(const unsigned &u, const unsigned &q) {
    //error handle
    if(loginUser.find(u) == loginUser.cend()) {
        cerr << "[UserManager followUsers] Invalid followUsers : " << u << " not login.\n";
        return false;
    }
    if(users.find(u) == users.cend()) {
        cerr << "[UserManager followUsers] Invalid followUsers : " << u << " not exist.\n";
        return false;
    }
    if(users.find(q) == users.cend()) {
        cerr << "[UserManager followUsers] Invalid followUsers : " << q << " not exist.\n";
        return false;
    }

    //execute
    if(users[q].privacy) {
        cerr << "[UserManager followUsers] Sorry, " << q << " is not allowed to be followed.\n";
        return false;
    }
    users[q].followerList.push_back(u);
    users[u].followList.push_back(q);
    return true;
}

bool UserManager::modifyPrivacy(const unsigned &u, const bool &adjust) {
    //error handle
    if(loginUser.find(u) == loginUser.cend()) {
        cerr << "[UserManager modifyPrivacy] Invalid modifyPrivacy : " << u << " not login.\n";
        return false;
    }
    if(users.find(u) == users.cend()) {
        cerr << "[UserManager modifyPrivacy] Invalid modifyPrivacy : " << u << " not exist.\n";
        return false;
    }

    users[u].privacy = adjust;
    return true;
}