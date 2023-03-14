//
// Created by 陆逸凡 on 2023/3/3.
//

#ifndef SPOT_PALM_CONST_VALUE_H
#define SPOT_PALM_CONST_VALUE_H
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

    unsigned getDifference(HOBBIES h) {
        same = 0;
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
};

#endif //SPOT_PALM_CONST_VALUE_H
