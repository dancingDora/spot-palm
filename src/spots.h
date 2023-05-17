//
// Created by 陆逸凡 on 2023/2/24.
//
#pragma once
#ifndef SPOT_PALM_SPOT_H
#define SPOT_PALM_SPOT_H

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "tools.h"
#include "global_status.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::cerr;
using std::ostream;
using std::cout;

class Status {

public:

    double temperature;//温度 1->5   cold -> hot
    double visitorAmount;//客流量 1->5   cold -> hot
    double humidity;//湿度 1->5   wet -> dry
    double consumption;//平均消费 1->5   low -> high
    double distance;//距离 1->5 short -> long

    Status();

    friend ostream & operator << (ostream &StatusOut, Status &status);

};

//a common comment : like(unsigned int), data(string)
class comment{

public:

    unsigned like; // sum of likes
    const unsigned uid; // user id who put this comment
    const unsigned time; // when put this comment
    Char<1024> data; // comment itself

    comment();

    explicit comment(const unsigned &u, const string &n);

};

//Comment Package : commentsMap(map<unsigned comment>) , size(int)
class Comments{

public:

    unordered_map<unsigned, comment*> commentsMap;
    unsigned size;

    Comments();

    void clear();

    unsigned len() const;

    void insert(const unsigned &u, const string &s);

    void remove(const unsigned &id, const string &s);

    comment* get(const unsigned &id);

    bool addYourLike(const unsigned &cid);

    comment* &operator [] (const unsigned &id);

};

class Spot {

public:

    Char<64> spotName;
    const int sid;
    Status status;
    const PROVINCE province; // 省份
    Char<64> city; // 城市
    const double NS, WE; //经纬度
    Comments comments; // 评论区（并非某一条评论），包装有 : unordered_map

public:

    Spot();

    Spot(const string &spotNameA, const int &sidA,
         const double &t, const double &v, const double &h, const double &c, const double &d,
         const PROVINCE &provinceA, const string &cityA,
         const double & NSA, const double & WEA);

    Spot(const Spot &s);

    friend ostream& operator << (ostream &SpotOut, const Spot &spot);

    friend bool operator < (const Spot &l, const Spot &r);

    friend bool operator > (const Spot &l, const Spot &r);

    friend bool operator <= (const Spot &l, const Spot &r);

    friend bool operator >= (const Spot &l, const Spot &r);

    friend bool operator == (const Spot &l, const Spot &r);

    friend bool operator != (const Spot &l, const Spot &r);


};

class SpotManager {
public:

    unordered_map<unsigned , Spot*> spots;//sid - spots
    unordered_map<string, vector<Spot*> > province_spots;
    unordered_map<string, Spot*> name_spots;

//    GlobalStatus global_status;

public:

    SpotManager();

    ~SpotManager();

    bool addSpot(const string &spotNameA, const int &sidA,
                 const double &t, const double &v, const double &h, const double &c, const double &d,
                 const PROVINCE &provinceA, const string &cityA,
                 const double & NSA, const double & WEA);

    bool addSpot(const Spot &spot);

    bool clear();

    bool putComment(const unsigned &s, const unsigned &u, const unsigned &c, const string &data);

    bool putCommentLike(const unsigned &s, const unsigned &u, const unsigned &c);


};

#endif //SPOT_PALM_SPOT_H