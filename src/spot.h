//
// Created by 陆逸凡 on 2023/2/24.
//

#ifndef SPOT_PALM_SPOT_H
#define SPOT_PALM_SPOT_H
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "tools.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::cerr;
using std::ostream;
using std::cout;

class Status {
public:
    double temp;//温度 1->5   cold -> hot
    double visitorAmount;//客流量 1->5   cold -> hot
    double humidity;//湿度 1->5   wet -> dry
    double consumption;//平均消费 1->5   low -> high
    double distance;//距离 1->5 short -> long

    Status(){
        temp = visitorAmount = humidity = consumption = distance = 3;
    };
    friend ostream & operator << (ostream &StatusOut, Status &status) {
        StatusOut << "Here temprature is " << status.temp << '\n';
        StatusOut << "visitor amount is " << status.visitorAmount << '\n';
        StatusOut << "humidity is " << status.humidity << '\n';
        StatusOut << "consumption is " << status.consumption << '\n';
        StatusOut << "distance is " << status.distance << '\n';
        StatusOut << "And these are the whole detailed information of status.\n";
        return StatusOut;
    }
};

class Spot {
public:
    Char<64> spotName;
    const int sid;
    Status status;
    const PROVINCE province;//
    Char<64> city;//城市
    const double NS, WE;//经纬度
public:
    Spot():NS(39.9042), WE(116.4074), province(Beijing), sid(0) {
        status.visitorAmount = status.humidity = status.consumption = status.distance = status.temp = 3;
    }
    Spot(const string &spotNameA, const int &sidA,
         const double &t, const double &v, const double &h, const double &c, const double &d,
         const PROVINCE &provinceA, const string &cityA,
         const double & NSA, const double & WEA)
         : province(provinceA), NS(NSA), WE(WEA), sid(sidA){
        spotName = spotNameA;
        status.temp = t;
        status.distance = d;
        status.consumption = c;
        status.humidity = h;
        status.visitorAmount = v;
        city = cityA;
    }
    Spot(const Spot &s) : province(s.province), NS(s.NS), WE(s.WE), sid(s.sid) {
        spotName = s.spotName;
        status.temp = s.status.temp;
        status.distance = s.status.distance;
        status.consumption = s.status.consumption;
        status.humidity = s.status.humidity;
        status.visitorAmount = s.status.visitorAmount;
        city = s.city;
    }
    friend ostream& operator << (ostream &SpotOut, const Spot &spot) {
        SpotOut << "The Spot's spot id : " << spot.sid << '\n';
        SpotOut << "              Name : " << spot.spotName << '\n';
        SpotOut << "in the " << provToS(spot.province) << " , " << spot.city << '\n' << '\n';
        SpotOut <<  &spot.status;
        return SpotOut;
    }
};

class SpotManager {
public:
    Spot *s;
    unordered_map<int, Spot> spots;//sid - spots
    unordered_map< string, vector<Spot> > province_spots;
public:
    SpotManager() {
        spots.clear();
        province_spots.clear();
    }
    ~SpotManager() {
        spots.clear();
        province_spots.clear();
    }
    bool addSpot(const string &spotNameA, const int &sidA,
                 const double &t, const double &v, const double &h, const double &c, const double &d,
                 const PROVINCE &provinceA, const string &cityA,
                 const double & NSA, const double & WEA) {
        if(spots.find(sidA) != spots.cend()) {
            cerr << "[SpotManager addSpot(...)] Invalid logout : " << sidA << " exists.\n";
            return 0;
        }
        Spot *newSpot = new Spot(spotNameA, sidA,
                                 t,v,h,c,d,
                                 provinceA, cityA,
                                 NSA, WEA);
        spots.insert(std::pair<int, Spot>(sidA, *newSpot));
        province_spots[provToS(newSpot->province)].push_back(*newSpot);
        return true;
    };
    bool addSpot(const Spot &spot) {
        if(spots.find(spot.sid) != spots.cend()) {
            cerr << "[SpotManager addSpot(Spot)] Invalid logout : " << spot.sid << " exists.\n";
            return false;
        }
        Spot *newSpot = new Spot(spot);
        spots.insert(std::pair<int, Spot>(spot.sid, *newSpot));
        province_spots[provToS(newSpot->province)].push_back(*newSpot);
        return true;
    };
    bool clear() {
        spots.clear();
        province_spots.clear();
        return true;
    }
};


#endif //SPOT_PALM_SPOT_H