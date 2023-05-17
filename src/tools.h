//
// Created by 陆逸凡 on 2023/4/12.
//
#pragma once
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

/*
已知两点经纬度，计算球面距离（地球半径默认值为 6371.0 ( const_value.h EARTH_RADIUS))
*/
double toRadians(double degree);

double distance(double lat1, double lon1, double lat2, double lon2);

/*
一个可以把enum PROVINCE类型转化为string的方法
 (PROVINCE)province -> return (string)"province"
*/
string provToS(const PROVINCE &p);

PROVINCE sToProv(const string &s);

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

bool help();

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

/*需要一个统计区间重叠数量的算法，返回一段区间（pair）或者区间的中点
 */

/*
 * hash :
 * unsigned hashUSunsigned u, unsigned s);
 */

uint32_t hashUS(const unsigned &u, const unsigned &s);

// int[] to status
// order : temperature,     humidity,   consumption,
//         100-400          n% * 100    n
//
//      visitorAmount,      distance
//      log_10^(n) * 100    log_10^n(km) * 100
//

//interval 只能用构造函数(double ll, double rr)赋值

class Interval {
public:
    int ll;
    int rr;
    bool empty;

    Interval() {
        ll = rr = 0;
        empty = true;
    }

    Interval(const int &l, const int &r) {
        ll = l, rr = r;
        bool invalid = ll > rr;
        empty = (!ll & !rr) || invalid;
        if (empty) ll = rr = -1;
    }

    friend std::istream &operator>>(std::istream &pin, Interval interval) {
        pin >> interval.ll >> interval.rr;
        interval.empty = interval.ll > interval.rr;
        return pin;
    };
};

struct PreferenceInterval {

    Interval *temperature;
    Interval *visitorAmount;
    Interval *humidity;
    Interval *consumption;
    Interval *distance;

    friend std::istream &operator>>(std::istream &pin, PreferenceInterval preferenceInterval) {
        for (int i = 0; i < 4; i++)
            pin >> preferenceInterval.temperature[i];
        for (int i = 0; i < 4; i++)
            pin >> preferenceInterval.visitorAmount[i];
        for (int i = 0; i < 4; i++)
            pin >> preferenceInterval.humidity[i];
        for (int i = 0; i < 4; i++)
            pin >> preferenceInterval.consumption[i];
        for (int i = 0; i < 4; i++)
            pin >> preferenceInterval.distance[i];
        return pin;
    }
};

class Point {
public:
    int pos;
    int weight;
    Point *nxt;
    Point *frt;

    Point(const int &pos, const int &weight, Point *front = NULL, Point *next = NULL)
            : pos(pos), weight(weight), nxt(next), frt(front) {};

    ~Point() {
        delete nxt;
        delete frt;
    }

};

class Axis {

private:

    Point *head;

public:

    Axis() : head(nullptr) {};

    Axis &operator+(const Interval &interval) {
        insert(interval);
        return *this;
    }

    Axis &operator-(const Interval &interval) {
        remove(interval);
        return *this;
    }

    Axis operator[](const Interval &interval) const {
        Axis *res = copyAxis(*this);
        Point *ptr = res->find(interval.ll);
        res->head = ptr;
        ptr->frt = new Point(0, 0, NULL, NULL);
        while (ptr->nxt && ptr->nxt->pos <= interval.rr) {
            ptr = ptr->nxt;
        }
        if (ptr->nxt)
            ptr->nxt = nullptr;
        return *res;
    }

    int operator[](const int &pos) const {
        Point *ptr = head;
        while (ptr) {
            if (ptr->pos == pos) return ptr->weight;
            else if (ptr->pos < pos) ptr = ptr->nxt;
            else if (ptr->pos > pos) return ptr->frt->weight;
        }
        return 0;
    }

    Axis &operator+=(const Interval &interval) {
        *this = *this + interval;
        return *this;
    }

    Axis &operator-=(const Interval &interval) {
        *this = *this - interval;
        return *this;
    }

    int highest() {
        if (!head) return -1;
        Point *ptr = head;
        int weight = head->weight;
        while (ptr->nxt) {
            if (ptr->weight > weight) weight = ptr->weight;
            ptr = ptr->nxt;
        }
        return weight;
    }

private:

    Point *find(const int &pos) {
        Point *ptr = head;
        while (ptr) {
            if (ptr->pos == pos) return ptr;
            if (ptr->pos < pos)
                if (ptr->nxt)ptr = ptr->nxt;
                else {
                    Point *newPoint = new Point(pos, 0, ptr, nullptr);
                    ptr->nxt = newPoint;
                    return newPoint;
                }
            else if (ptr->pos > pos) {
                Point *newPoint = new Point(pos, ptr->frt->weight, ptr->frt, ptr);
                ptr->frt->nxt = newPoint;
                ptr->frt = newPoint;
                return newPoint;
            }
        }
        return nullptr;
    }

    bool insert(const Interval &interval) {
        if (interval.empty) return false;
        if (head == nullptr) {
            head = new Point(interval.ll, 1, nullptr, nullptr);
            head->nxt = new Point(interval.rr, 0, head, nullptr);
            return true;
        }
        Point *start = find(interval.ll);
        Point *end = find(interval.rr);
        for (Point *it = start; it != end; it = it->nxt)
            it->weight++;
        return true;
    }

    bool remove(const Interval &interval) {
        if (interval.empty) return false;
        Point *start = find(interval.ll);
        Point *end = find(interval.rr);
        for (Point *it = start; it != end; it = it->nxt)
            it->weight--;
        return true;
    }

    Axis *copyAxis(const Axis &x) const {
        Axis *res = new Axis();
        res->head = new Point(x.head->pos, x.head->weight);
        Point *ptrToRes = res->head;
        Point *ptr = x.head->nxt;
        while (ptr) {
            Point *tmp = new Point(ptr->pos, ptr->weight);
            ptrToRes->nxt = tmp;
            tmp->frt = ptrToRes;
            ptrToRes = tmp;

            ptr = ptr->nxt;
        }
        return res;
    }

};

unsigned s_to_u(string num);
#endif //旅游景点模糊推荐_TOOLS_H
