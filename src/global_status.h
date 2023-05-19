//
// Created by 陆逸凡 on 2023/4/2.
//
#pragma once
#ifndef SPOT_PALM_QUESTIONARE_H
#define SPOT_PALM_QUESTIONARE_H

#include <iostream>
#include "tools.h"

class GlobalStatus {

private:

    Axis *temperature[5];
    Axis *visitorAmount[5];
    Axis *humidity[5];
    Axis *consumption[5];
    Axis *distance[5];

    int t[4];
    int v[4];
    int h[4];
    int c[4];
    int d[4];

public:

    bool questionnaire();

    GlobalStatus();

    bool modifyStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval);

    int highestPos(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum) const;

    bool flashAxis();

    bool cheat(int a[], int b[], int c[], int d[], int e[]);


    //spot -- gloval_status
    // for spot`s status setting level
    int setLevel(const STATUS_ENUM &statusEnum, int parameter);
private:

    bool addStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval);



};


#endif //SPOT_PALM_QUESTIONARE_H
