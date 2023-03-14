//
// Created by 陆逸凡 on 2023/3/3.
//

#ifndef SPOT_PALM_CONST_VALUE_H
#define SPOT_PALM_CONST_VALUE_H
#include <iostream>
using std::cout;
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

#endif //SPOT_PALM_CONST_VALUE_H
