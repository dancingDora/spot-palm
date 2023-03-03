//
// Created by 陆逸凡 on 2023/2/24.
//

#ifndef SPOT_PALM_SPOT_H
#define SPOT_PALM_SPOT_H
#include <unordered_map>
#include <vector>
#include "tools.h"

using std::string;
using std::unordered_map;
using std::cerr;

enum PROVINCE {//省级行政区 34
    Beijing,Tianjin,Shanghai,Chongqing, // 直辖市 4
    Guangxi,Neimenggu,Ningxia,Xizang,Xinjiang,//自治区 5
    Anhui,Fujian,Gansu,Guangdong,Guizhou,//A-G 5
    Hainan,Hebei,Henan,Heilongjiang,Hubei,Hunan,Jilin,Jiangsu,Jiangxi,//H-J 9
    Liaoning,Qinghai,Shandong,Shanxi,Shaanxi,Sichuan,Taiwan,Yunnan,Zhejiang,//L-Z 9
    Xianggang,Aomen,//特别行政区 2
};
struct Status {
    double temp;//温度 1->5   cold -> hot
    double visitorAmount;//客流量 1->5   cold -> hot
    double humidity;//湿度 1->5   wet -> dry
    double consumption;//平均消费 1->5   low -> high
    double distance;//距离 1->5 short -> long

    Status(){
        temp = visitorAmount = humidity = consumption = distance = 3;
    };
};

class Spot {
public:
    Char<64> spotName;
    const int sid;
    Status status;
    const PROVINCE province;//
    Char<64> city;//城市
    const double NS, WE;//经纬度
private:
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
};

class SpotManager {
    unordered_map<int, Spot> spots;//sid - spots
    unordered_map<double, Spot> province_spots;
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
            cerr << "[SpotManager addSpot] Invalid logout : " << sidA << " exists.\n";
            return 0;
        }

    };
    bool addSpot()
};


#endif //SPOT_PALM_SPOT_H