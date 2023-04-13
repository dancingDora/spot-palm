//
// Created by 陆逸凡 on 2023/4/12.
//

#ifndef SPOT_PALM_CONST_VALUE_H
#define SPOT_PALM_CONST_VALUE_H
#define ROOT_PASSWORD root_password
const double EARTH_RADIUS = 6371.0;
enum PROVINCE {//省级行政区 34
    Beijing,Tianjin,Shanghai,Chongqing, // 直辖市 4
    Guangxi,Neimenggu,Ningxia,Xizang,Xinjiang,//自治区 5
    Anhui,Fujian,Gansu,Guangdong,Guizhou,//A-G 5
    Hainan,Hebei,Henan,Heilongjiang,Hubei,Hunan,Jilin,Jiangsu,Jiangxi,//H-J 9
    Liaoning,Qinghai,Shandong,Shanxi,Shaanxi,Sichuan,Taiwan,Yunnan,Zhejiang,//L-Z 9
    Xianggang,Aomen//特别行政区 2
};
//TODO : 用户自画像：用于交友
enum ZODIAC_SIGNS {
    Aries,
    Taurus,
    Gemini,
    Cancer,
    Leo,
    Virgo,
    Libra,
    Scorpio,
    Sagittarius,
    Capricorn,
    Aquarius,
    Pisces
};

enum STATUS_ENUM {
    Temperature,
    VisitorAmount,
    Humidity,
    Consumption,
    Distance
};

enum STATUS_DEGREE {
    LOW,
    MID_LOW,
    MEDIUM,
    MID_HIGH,
    HIGH
};


#endif //SPOT_PALM_CONST_VALUE_H

