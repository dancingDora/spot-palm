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
        case Beijing :
            return "Beijing";
        case Tianjin :
            return "Tianjin";
        case Shanghai :
            return "Shanghai";
        case Chongqing :
            return "Chongqing";
        case Guangxi :
            return "Guangxi";
        case Neimenggu :
            return "Neimenggu";
        case Ningxia :
            return "Ningxia";
        case Xizang :
            return "Xizang";
        case Xinjiang :
            return "Xinjiang";
        case Anhui :
            return "Anhui";
        case Fujian :
            return "Fujian";
        case Gansu :
            return "Gansu";
        case Guangdong :
            return "Guangdong";
        case Guizhou :
            return "Guizhou";
        case Hainan :
            return "Hainan";
        case Hebei :
            return "Hebei";
        case Henan :
            return "Henan";
        case Heilongjiang :
            return "Heilongjiang";
        case Hubei :
            return "Hubei";
        case Hunan :
            return "Hunan";
        case Jilin :
            return "Jilin";
        case Jiangsu :
            return "Jiangsu";
        case Jiangxi :
            return "Jiangxi";
        case Liaoning :
            return "Liaoning";
        case Qinghai :
            return "Qinghai";
        case Shandong :
            return "Shandong";
        case Shanxi :
            return "Shanxi";
        case Shaanxi :
            return "Shaanxi";
        case Sichuan :
            return "Sichuan";
        case Taiwan :
            return "Taiwan";
        case Yunnan :
            return "Yunnan";
        case Zhejiang :
            return "Zhejiang";
        case Xianggang :
            return "Xianggang";
        case Aomen :
            return "Aomen";
        default :
            cerr << "[tools.h/provToS] Wrong in , no such province.\n";
    }
    return "";
}

PROVINCE sToProv(const string &s) {
    if (s == "Beijing") return Beijing;
    if (s == "Tianjin") return Tianjin;
    if (s == "Shanghai") return Shanghai;
    if (s == "Chongqing") return Chongqing;
    if (s == "Guangxi") return Guangxi;
    if (s == "Neimenggu") return Neimenggu;
    if (s == "Ningxia") return Ningxia;
    if (s == "Xizang") return Xizang;
    if (s == "Xinjiang") return Xinjiang;
    if (s == "Anhui") return Anhui;
    if (s == "Fujian") return Fujian;
    if (s == "Gansu") return Gansu;
    if (s == "Guangdong") return Guangdong;
    if (s == "Guizhou") return Guizhou;
    if (s == "Hainan") return Hainan;
    if (s == "Hebei") return Hebei;
    if (s == "Henan") return Henan;
    if (s == "Heilongjiang") return Heilongjiang;
    if (s == "Hubei") return Hubei;
    if (s == "Hunan") return Hunan;
    if (s == "Jilin") return Jilin;
    if (s == "Jiangsu") return Jiangsu;
    if (s == "Jiangxi") return Jiangxi;
    if (s == "Liaoning") return Liaoning;
    if (s == "Qinghai") return Qinghai;
    if (s == "Shandong") return Shandong;
    if (s == "Shanxi") return Shanxi;
    if (s == "Shaanxi") return Shaanxi;
    if (s == "Sichuan") return Sichuan;
    if (s == "Taiwan") return Taiwan;
    if (s == "Yunnan") return Yunnan;
    if (s == "Zhejiang") return Zhejiang;
    if (s == "Xianggang") return Xianggang;
    if (s == "Aomen") return Aomen;
    cerr << "[tools.h/sToProv] Wrong, the string is not right.\n";
}

/*
 * class TokenScanner
 * 读入参数 : getline来读入
 */
class TokenScanner {
public:
    size_t pos;
    string Buffer;

    TokenScanner() : pos(0) {};

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
        return Buffer.substr(pos, l + 1 - pos);
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
    cout
            << "\033[36mWe will give you good recommend for spot as we can. And here is the usage of command line version.\033[0m"
            << std::endl << std::endl;
    cout
            << "\033[36m   add_user -n <user_name(string)> -v <privilege(int)> -g <gender(int)> -m <mail_address(string)> -i <uid(unsigned)> -p <password(string)>\033[0m"
            << std::endl;
    cout << "\033[36m   login -i <uid(unsigned)> -p <password(string)>\033[0m" << std::endl;
    cout << "\033[36m   logout -i <uid(unsigned)>\033[0m" << std::endl;
    cout << "\033[36m   query_profile -i <uid(unsigned)> -q <queryUID(unsigned)>\033[0m" << std::endl;
    cout
            << "\033[36m   modify_profile -i <uid(unsigned)> (-g) <gender(int)> (-m) <mail_address(string)> (-n_ <name(string)>\033[0m"
            << std::endl;
    cout << "\033[36m   add_spot -n [spot name] -i [sid] -t [status temperature] -v [status visitorAmount]\033[0m"
         << std::endl;
    cout << "\033[33m            -h [status humidity] -c [status consumption] -d [status distance]\033[0m" << std::endl;
    cout << "\033[33m            -p [province] -s [city] -ns [NS] -we [WE]\033[0m" << std::endl;
    cout << "\033[33m   --help   (give you the usage method, just repeat such output) \033[0m" << std::endl;
    cout << "\033[33m   clear pw (clear all the data, only input the password of root can be done.)\033[0m" << std::endl
         << std::endl;
    cout << "\033[30mThe sequence of parameter is free.\033[0m\n";
    cout << "\033[30mEnjoy the spot-palm now!\033[0m" << std::endl;
}

class HOBBIES {
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
        if (swim && h.swim) same++;
        if (run && h.run)same++;
        if (cycle && h.cycle) same++;
        if (basketball && h.basketball) same++;
        if (football && h.football) same++;
        if (tennis && h.tennis) same++;
        if (table_tennis && h.table_tennis) same++;
        if (box && h.box) same++;
        if (shoot && h.shoot) same++;
        if (volleyball && h.volleyball) same++;
        if (baseball && h.baseball) same++;
        if (gymnastic && h.gymnastic) same++;
        if (sky && h.sky) same++;
        if (ice_skating && h.ice_skating) same++;
        if (marathon && h.marathon) same++;
        if (row && h.row) same++;
        if (surf && h.surf) same++;
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

    friend std::ostream &operator<<(std::ostream &hout, const HOBBIES &h) {
        hout << "Sports Part : ";
        if (h.swim) hout << "swim\t";
        if (h.run) hout << "run\t";
        if (h.cycle) hout << "cycle\t";
        if (h.basketball) hout << "basketball\t";
        if (h.football) hout << "football\t";
        if (h.tennis) hout << "tennis\t";
        if (h.table_tennis) hout << "table_tennis\t";
        if (h.box) hout << "box\t";
        if (h.shoot) hout << "shoot\t";
        if (h.volleyball) hout << "volleyball\t";
        if (h.baseball) hout << "baseball\t";
        if (h.gymnastic) hout << "gymnastic\t";
        if (h.sky) hout << "sky\t";
        if (h.ice_skating) hout << "ice_skating\t";
        if (h.marathon) hout << "marathon\t";
        if (h.row) hout << "row\t";
        if (h.surf) hout << "surf\n";
        hout << "Music Part : ";
        if (h.classical) hout << "classical\t";
        if (h.jazz_blues) hout << "jazz_blues\t";
        if (h.folk) hout << "folk\t";
        if (h.pop) hout << "pop\t";
        if (h.rock) hout << "rock\t";
        if (h.dance) hout << "dance\t";
        if (h.rap) hout << "rap\t";
        if (h.electronic) hout << "electronic\t";
        return hout;
    }
};

int monthDay[] = {0, 31, 28, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};

/*
 * judge is a year (y : unsigned) leap or not
 */
bool isLeap(unsigned y) {
    return !(y % 4) && (y % 100) || !(y % 400);
}

//format : 20XX-XX-XX--23:59:00
//         0    5  8   12 15 18
class Date {
public:
    unsigned int year;
    unsigned int month;
    unsigned int day;

    Date() : year(2004), month(1), day(2) {};

    Date(const unsigned &y, const unsigned &m, const unsigned &d) {
        year = y, month = m, day = d;
    }

    unsigned dt_to_u(Date &d) {
        unsigned des = d.year, res = 0;
        for (unsigned i = 1; i < des; i++)
            if (isLeap(i))
                res += 1;
        res += (365 * (des - 1));
        if (isLeap(d.year) && d.month > 2)
            res += 1;
        for (int i = 1; i < d.month; i++)
            res += monthDay[i];
        res += d.day;
        return res;
    }

    Date u_to_dt(unsigned &u) {
        unsigned resY, resM, resD;
        resY = resM = resD = 0;

        unsigned basic = u / 366;
        unsigned delta = 0;
        for (unsigned i = 0; i < basic; i++)
            if (isLeap(i))
                delta += 1;
        delta += (365 * basic);
        u -= delta;
        resY = basic;
        while (u > 366) {
            if (isLeap(resY))
                u -= 1;
            u -= 365;
            resY++;
        }
        if (isLeap(resY) && u == 60) {
            return Date(resY, 2, 29);
        } else if (isLeap(resY) && u > 60)
            u--;
        for (int i = 1; u > 0 && i <= 12; i++) {
            if (u > monthDay[i])
                u -= monthDay[i];
            else return Date(resY, i, u);
        }
        return Date(resY, 1, u);
    }


    friend Date operator+(const Date &l, const unsigned &r) {
        unsigned ll =
    }

    friend Date operator-(const Date &l, const unsigned &r) {

    }

};
unsigned dt_to_u(Date &d) {
    unsigned des = d.year, res = 0;
    for (unsigned i = 1; i < des; i++)
        if (isLeap(i))
            res += 1;
    res += (365 * (des - 1));
    if (isLeap(d.year) && d.month > 2)
        res += 1;
    for (int i = 1; i < d.month; i++)
        res += monthDay[i];
    res += d.day;
    return res;
}

Date u_to_dt(unsigned &u) {
    unsigned resY, resM, resD;
    resY = resM = resD = 0;

    unsigned basic = u / 366;
    unsigned delta = 0;
    for (unsigned i = 0; i < basic; i++)
        if (isLeap(i))
            delta += 1;
    delta += (365 * basic);
    u -= delta;
    resY = basic;
    while (u > 366) {
        if (isLeap(resY))
            u -= 1;
        u -= 365;
        resY++;
    }
    if (isLeap(resY) && u == 60) {
        return Date(resY, 2, 29);
    } else if (isLeap(resY) && u > 60)
        u--;
    for (int i = 1; u > 0 && i <= 12; i++) {
        if (u > monthDay[i])
            u -= monthDay[i];
        else return Date(resY, i, u);
    }
    return Date(resY, 1, u);
}

class Clock {
public:
    unsigned int hour;
    unsigned int min;
    unsigned int sec;
    bool Day;

    Clock() : hour(0), min(0), sec(0), Day(false) {};

    Clock(const unsigned &h, const unsigned &m, const unsigned &s) : Day(false) {
        hour = h, min = m, sec = s;
    }

    bool check() {
        if (!Day) return Day;
        Day = false;
        return true;
    }

    friend unsigned unsignedInt(Clock &c) {
        unsigned res = c.hour * 3600 + c.min * 60 + c.sec;
        return res;
    }

};

class Time {
public:
    Date date;
    Clock clock;

public:
    Time() {
        date = Date();
        clock = Clock();
    };

    Time(const string &t) {
        date.year = (t[0] - '0') * 1000 +
                    (t[1] - '0') * 100 +
                    (t[2] - '0') * 10 +
                    (t[3] - '0');
        date.month = (t[5] - '0') * 10 +
                     (t[6] - '0');
        date.day = (t[8] - '0') * 10 +
                   (t[9] - '0');
        clock.hour = (t[12] - '0') * 10 +
                     (t[13] - '0');
        clock.min = (t[15] - '0') * 10 +
                    (t[16] - '0');
        clock.sec = (t[18] - '0') * 10 +
                    (t[19] - '0');
    }

    Time(const Time &t) {
        date.year = t.date.year;
        date.month = t.date.month;
        date.day = t.date.day;
        clock.hour = t.clock.hour;
        clock.min = t.clock.min;
        clock.sec = t.clock.sec;
    }

    /*
      format : 20001231235959
               ^   ^   ^ ^  ^
               14  10  6 4  1
                <--------2000 * 1e10
                   <-------12 * 1e8
                     <-----31 * 1e6
    */
    friend unsigned long long unsignedLong(const Time &t) {
        unsigned long long Year = t.date.year * 1e10;
        unsigned long long Month = t.date.month * 1e8;
        unsigned long long Day = t.date.day * 1e6;
        unsigned tt = (t.clock.hour * 10000) | (t.clock.min * 100) | (t.clock.sec);
        unsigned long long res = Year | Month | Day | tt;
        return res;
    }

    friend Time time(unsigned long long &t) {
        unsigned long long Year = t % (365 * 24 * 3600);
        t -= (t - Year * (365 * 24 * 3600));
        unsigned long long Day = t % (24 * 3600);
        t -= (t - Day * (24 * 3600));
        unsigned hour = t % 3600;
        t -= (t - hour * 3600);
        unsigned minute = t % 3600;
    }


    friend bool operator<(const Time &l, const Time &r) {
        return unsignedLong(l) < unsignedLong(r);
    }

    friend bool operator>(const Time &l, const Time &r) {
        return unsignedLong(l) > unsignedLong(r);
    }

    friend bool operator<=(const Time &l, const Time &r) {
        return unsignedLong(l) <= unsignedLong(r);
    }

    friend bool operator>=(const Time &l, const Time &r) {
        return unsignedLong(l) >= unsignedLong(r);
    }

    friend bool operator==(const Time &l, const Time &r) {
        return unsignedLong(l) == unsignedLong(r);
    }

    friend bool operator!=(const Time &l, const Time &r) {
        return unsignedLong(l) != unsignedLong(r);
    }

    friend Time operator+(const Time &l, const unsigned &r) {


    }
};

/*需要一个统计区间重叠数量的算法，返回一段区间（pair）或者区间的中点
 */

/*
 * hash :
 * unsigned hashUSunsigned u, unsigned s);
 */

unsigned hashUS(const unsigned &u, const unsigned &s) {
    return (u << 16) | (s & 0x0000ffffl);
}


#endif //旅游景点模糊推荐_TOOLS_H