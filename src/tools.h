//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_TOOLS_H
#define 旅游景点模糊推荐_TOOLS_H

#include <cstring>
#include <iostream>
#include <cmath>
#include "const_value.h"

using std::string;
using std::cerr;
using std::cout;
/*class Char<int>
 *
 */
template<const int size = 64>
class Char {
    char content[size + 1];

public:
    Char() { content[0] = '\0'; }
    Char(const std::string &s) { strcpy(content, s.c_str()); }
    Char(const char *cstr) { strcpy(content, cstr); }
    operator std::string() const { return str(); }
    std::string str() const { return std::string(content); }
    char *c_str() { return content; }
    char &operator[](int index) { return content[index]; }
    char operator[](int index) const { return content[index]; }
    Char &operator=(const Char &that) {
        if (this == &that) return *this;
        strcpy(content, that.content);
        return *this;
    }
    bool empty() const { return content[0] == '\0'; }
    friend bool operator<(const Char<size> &a, const Char<size> &b) { return strcmp(a.content, b.content) < 0; }
    friend bool operator==(const Char<size> &a, const Char<size> &b) { return strcmp(a.content, b.content) == 0; }
    friend bool operator>(const Char<size> &a, const Char<size> &b) { return strcmp(a.content, b.content) > 0; }
    friend bool operator<=(const Char<size> &a, const Char<size> &b) { return !(operator>(a, b)); }
    friend bool operator>=(const Char<size> &a, const Char<size> &b) { return !(operator<(a, b)); }
    friend bool operator!=(const Char<size> &a, const Char<size> &b) { return !(operator==(a, b)); }
    friend std::istream &operator>>(std::istream &is, Char<size> &s) { return is >> s.content; }
    friend std::ostream &operator<<(std::ostream &os, const Char<size> &s) { return os << s.content; }
};
//thank you teacher lin


/*
已知两点经纬度，计算球面距离（地球半径默认值为 6371.0 ( const_value.h EARTH_RADIUS))
*/
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double distance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = EARTH_RADIUS * c;
    return distance;
}

/*
一个可以把enum PROVINCE类型转化为string的方法
 (PROVINCE)province -> return (string)"province"
*/
string provToS(const PROVINCE &p) {
    switch (p) {//total 34
        case Beijing :return "Beijing";
        case Tianjin :return "Tianjin";
        case Shanghai :return "Shanghai";
        case Chongqing :return "Chongqing";
        case Guangxi :return "Guangxi";
        case Neimenggu :return "Neimenggu";
        case Ningxia :return "Ningxia";
        case Xizang :return "Xizang";
        case Xinjiang :return "Xinjiang";
        case Anhui :return "Anhui";
        case Fujian :return "Fujian";
        case Gansu :return "Gansu";
        case Guangdong :return "Guangdong";
        case Guizhou :return "Guizhou";
        case Hainan :return "Hainan";
        case Hebei :return "Hebei";
        case Henan :return "Henan";
        case Heilongjiang :return "Heilongjiang";
        case Hubei :return "Hubei";
        case Hunan :return "Hunan";
        case Jilin :return "Jilin";
        case Jiangsu :return "Jiangsu";
        case Jiangxi :return "Jiangxi";
        case Liaoning :return "Liaoning";
        case Qinghai :return "Qinghai";
        case Shandong :return "Shandong";
        case Shanxi :return "Shanxi";
        case Shaanxi :return "Shaanxi";
        case Sichuan :return "Sichuan";
        case Taiwan :return "Taiwan";
        case Yunnan :return "Yunnan";
        case Zhejiang :return "Zhejiang";
        case Xianggang :return "Xianggang";
        case Aomen :return "Aomen";
        default :cerr << "[tools.h/provToS] Wrong in , no such province.\n";
    }
    return "";
}
PROVINCE sToProv(const string &s) {
    if(s == "Beijing") return Beijing;
    if(s == "Tianjin") return Tianjin;
    if(s == "Shanghai") return Shanghai;
    if(s == "Chongqing") return Chongqing;
    if(s == "Guangxi") return Guangxi;
    if(s == "Neimenggu") return Neimenggu;
    if(s == "Ningxia") return Ningxia;
    if(s == "Xizang") return Xizang;
    if(s == "Xinjiang") return Xinjiang;
    if(s == "Anhui") return Anhui;
    if(s == "Fujian") return Fujian;
    if(s == "Gansu") return Gansu;
    if(s == "Guangdong") return Guangdong;
    if(s == "Guizhou") return Guizhou;
    if(s == "Hainan") return Hainan;
    if(s == "Hebei") return Hebei;
    if(s == "Henan") return Henan;
    if(s == "Heilongjiang") return Heilongjiang;
    if(s == "Hubei") return Hubei;
    if(s == "Hunan") return Hunan;
    if(s == "Jilin") return Jilin;
    if(s == "Jiangsu") return Jiangsu;
    if(s == "Jiangxi") return Jiangxi;
    if(s == "Liaoning") return Liaoning;
    if(s == "Qinghai") return Qinghai;
    if(s == "Shandong") return Shandong;
    if(s == "Shanxi") return Shanxi;
    if(s == "Shaanxi") return Shaanxi;
    if(s == "Sichuan") return Sichuan;
    if(s == "Taiwan") return Taiwan;
    if(s == "Yunnan") return Yunnan;
    if(s == "Zhejiang") return Zhejiang;
    if(s == "Xianggang") return Xianggang;
    if(s == "Aomen") return Aomen;
    cerr << "[tools.h/sToProv] Wrong, the string is not right.\n";
}

/*
 * class TokenScanner
 * 读入参数 : getline来读入
 */
class TokenScanner {
public:
    size_t  pos;
    string Buffer;
    TokenScanner() : pos(0){};

    TokenScanner(const string &str) : pos(0), Buffer(str) {};

    TokenScanner(const TokenScanner &t) : pos(t.pos), Buffer(t.Buffer) {};

    string NextToken(char delim = ' ') {
        if (pos >= Buffer.size()) {
            ++pos;
            return "";
        }
        size_t l;
        while (pos < Buffer.size() && Buffer[pos] == delim)pos++;
        l = pos;
        while (pos < Buffer.size() && Buffer[pos] != delim)pos++;
        return Buffer.substr(l, pos - l);
    }

    string getLeft(char delim = ' ') {
        if (pos == Buffer.size()) return "";
        while (pos < Buffer.size() && Buffer[pos] == delim) pos++;
        if (pos == Buffer.size()) return "";
        size_t l = Buffer.size() - 1;
        while (l >= pos && Buffer[l] == delim)l--;
        return Buffer.substr(pos,l+1-pos);
    }

    string NextToken(char delimL, char delimR, bool ck = 0) {
        if (pos == Buffer.size()) return "";
        while (pos < Buffer.size() && Buffer[pos] != delimL)++pos;
        size_t l = pos + 1 - ck;
        while (pos < Buffer.size() && Buffer[pos] != delimR)++pos;
        return Buffer.substr(l, pos++ - l);  // 修改：++
    }

    void Clear() {
        Buffer.clear();
        pos = 0;
    }
};

bool help() {
    cout << "\033[36m     ^_^       Welcome to spot palm ~\033[0m" << std::endl << std::endl;
    cout << "\033[36mWe will give you good recommend for spot as we can. And here is the usage of command line version.\033[0m" << std::endl << std::endl;
    cout << "\033[36m   add_user -n <user_name(string)> -v <privilege(int)> -g <gender(int)> -m <mail_address(string)> -i <uid(unsigned)> -p <password(string)>\033[0m" << std::endl;
    cout << "\033[36m   login -i <uid(unsigned)> -p <password(string)>\033[0m" << std::endl;
    cout << "\033[36m   logout -i <uid(unsigned)>\033[0m" << std::endl;
    cout << "\033[36m   query_profile -i <uid(unsigned)> -q <queryUID(unsigned)>\033[0m" << std::endl;
    cout << "\033[36m   modify_profile -i <uid(unsigned)> (-g) <gender(int)> (-m) <mail_address(string)> (-n_ <name(string)>\033[0m" << std::endl;
    cout << "\033[36m   add_spot -n [spot name] -i [sid] -t [status temperature] -v [status visitorAmount]\033[0m" << std::endl;
    cout << "\033[33m            -h [status humidity] -c [status consumption] -d [status distance]\033[0m" << std::endl;
    cout << "\033[33m            -p [province] -s [city] -ns [NS] -we [WE]\033[0m" << std::endl;
    cout << "\033[33m   --help   (give you the usage method, just repeat such output) \033[0m" << std::endl;
    cout << "\033[33m   clear pw (clear all the data, only input the password of root can be done.)\033[0m" << std::endl << std::endl;
    cout << "\033[30mThe sequence of parameter is free.\033[0m\n";
    cout << "\033[30mEnjoy the spot-palm now!\033[0m" << std::endl;
}

class HOBBIES{
    //SPORTS 17bits
public:
    bool swim;
    bool run;
    bool cycle;
    bool basketball;
    bool football;
    bool tennis;
    bool table_tennis;
    bool box;
    bool shoot;
    bool volleyball;
    bool baseball;
    bool gymnastic;
    bool sky;
    bool ice_skating;
    bool marathon;
    bool row;
    bool surf;
    //MUSIC 8bits
    bool classical;
    bool jazz_blues;
    bool folk;
    bool pop;
    bool rock;
    bool dance;
    bool rap;
    bool electronic;
    unsigned same;

    unsigned getDifference(const HOBBIES &h) {
        same = 0;
//        cout << "h    :\n" << h << '\n';
//        cout << "this :\n" << *this << '\n';

        //sports
        if(swim && h.swim) same++;
        if(run && h.run)same++;
        if(cycle && h.cycle) same++;
        if(basketball && h.basketball) same++;
        if(football && h.football) same++;
        if(tennis && h.tennis) same++;
        if(table_tennis && h.table_tennis) same++;
        if(box && h.box) same++;
        if(shoot && h.shoot) same++;
        if(volleyball && h.volleyball) same++;
        if(baseball && h.baseball) same++;
        if(gymnastic && h.gymnastic) same++;
        if(sky && h.sky) same++;
        if(ice_skating && h.ice_skating) same++;
        if(marathon && h.marathon) same++;
        if(row && h.row) same++;
        if(surf && h.surf) same++;
        //music
        if (classical && h.classical) same++;
        if (jazz_blues && h.jazz_blues) same++;
        if (folk && h.folk) same++;
        if (pop && h.pop) same++;
        if (rock && h.rock) same++;
        if (dance && h.dance) same++;
        if (rap && h.rap) same++;
        if (electronic && h.electronic) same++;

        return same;
    }

public:
    HOBBIES() {
        swim = false;
        run = false;
        cycle = false;
        basketball = false;
        football = false;
        tennis = false;
        table_tennis = false;
        box = false;
        shoot = false;
        volleyball = false;
        baseball = false;
        gymnastic = false;
        sky = false;
        ice_skating = false;
        marathon = false;
        row = false;
        surf = false;
        classical = false;
        jazz_blues = false;
        folk = false;
        pop = false;
        rock = false;
        dance = false;
        rap = false;
        electronic = false;

        same = 0;
    }
    friend std::ostream &operator << (std::ostream &hout, const HOBBIES &h) {
        hout << "Sports Part : ";
        if(h.swim) hout << "swim\t";
        if(h.run) hout << "run\t";
        if(h.cycle) hout << "cycle\t";
        if(h.basketball) hout << "basketball\t";
        if(h.football) hout << "football\t";
        if(h.tennis) hout << "tennis\t";
        if(h.table_tennis) hout << "table_tennis\t";
        if(h.box) hout << "box\t";
        if(h.shoot) hout << "shoot\t";
        if(h.volleyball) hout << "volleyball\t";
        if(h.baseball) hout << "baseball\t";
        if(h.gymnastic) hout << "gymnastic\t";
        if(h.sky) hout << "sky\t";
        if(h.ice_skating) hout << "ice_skating\t";
        if(h.marathon) hout << "marathon\t";
        if(h.row) hout << "row\t";
        if(h.surf) hout << "surf\n";
        hout << "Music Part : ";
        if(h.classical) hout << "classical\t";
        if(h.jazz_blues) hout << "jazz_blues\t";
        if(h.folk) hout << "folk\t";
        if(h.pop) hout << "pop\t";
        if(h.rock) hout << "rock\t";
        if(h.dance) hout << "dance\t";
        if(h.rap) hout << "rap\t";
        if(h.electronic) hout << "electronic\t";
        return hout;
    }
};

/*需要一个统计区间重叠数量的算法，返回一段区间（pair）或者区间的中点
 */

#endif //旅游景点模糊推荐_TOOLS_H
