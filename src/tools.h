//
// Created by 陆逸凡 on 2023/2/17.
//

#ifndef 旅游景点模糊推荐_TOOLS_H
#define 旅游景点模糊推荐_TOOLS_H

#include <cstring>
#include <iostream>
#include <cmath>
#include "const_value.h"

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
 * 已知两点经纬度，计算球面距离（地球半径默认值为 6371.0 ( const_value.h EARTH_RADIUS)
 *
 *
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



//需要一个统计区间重叠数量的算法，返回一段区间（pair）或者区间的中点
template<class T = int>
class intervalOverlap{
public:
    struct lr{
        T l;
        T r;
    };

    std::vector<lr*> e;


};



#endif //旅游景点模糊推荐_TOOLS_H
