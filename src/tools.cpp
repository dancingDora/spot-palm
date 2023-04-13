//
// Created by 陆逸凡 on 2023/4/13.
//
#include "tools.h"
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
    return Beijing;
}

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
    return true;
}

uint32_t hashUS(const unsigned &u, const unsigned &s) {
    uint32_t res = (u << 16) | (s & 0x0000ffffl);
    return res;
}