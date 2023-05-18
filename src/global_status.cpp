//
// Created by 陆逸凡 on 2023/4/2.
//

#include "global_status.h"

GlobalStatus::GlobalStatus() {
    for(int i = 0; i < 5; i++) {
        temperature[i] = new Axis();
        visitorAmount[i] = new Axis();
        humidity[i] = new Axis();
        consumption[i] = new Axis();
        distance[i] = new Axis();
    }
};

PreferenceInterval GlobalStatus::questionnaire() {

};

bool GlobalStatus::modifyStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval) {
    return true;
};

int GlobalStatus::highestPos(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum) const {
    Axis *statusPtr;
    switch(statusEnum) {
        case Temperature:
            statusPtr = temperature[statusDegree];
            return statusPtr->highestPos();
        case VisitorAmount:
            statusPtr = visitorAmount[statusDegree];
            return statusPtr->highestPos();
        case Humidity:
            statusPtr = humidity[statusDegree];
            return statusPtr->highestPos();
        case Consumption:
            statusPtr = consumption[statusDegree];
            return statusPtr->highestPos();
        case Distance:
            statusPtr = distance[statusDegree];
            return statusPtr->highestPos();
    }
};

bool GlobalStatus::addStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval) {
    //memory allocation & point to ...
    Axis *statusPtr = new Axis();
    switch(statusEnum) {
        case Temperature:
            statusPtr = temperature[statusDegree];
            break;
        case VisitorAmount:
            statusPtr = visitorAmount[statusDegree];
            break;
        case Humidity:
            statusPtr = humidity[statusDegree];
            break;
        case Consumption:
            statusPtr = consumption[statusDegree];
            break;
        case Distance:
            statusPtr = distance[statusDegree];
            break;
    }

    if(interval.empty) return false;

    //execute add status
    *statusPtr += interval;
    return true;
};

bool GlobalStatus::flashAxis() {
    int tmp = temperature[0]->highestPos();
    for(int i = 0; i < 4; i++) {
        t[i] = (tmp + temperature[i + 1]->highestPos()) / 2;
        tmp = t[i] * 2 - tmp;
    }
    tmp = humidity[0]->highestPos();
    for(int i = 0; i < 4; i++) {
        h[i] = (tmp + humidity[i + 1]->highestPos()) / 2;
        tmp = h[i] * 2 - tmp;
    }
    tmp = visitorAmount[0]->highestPos();
    for(int i = 0; i < 4; i++) {
        v[i] = (tmp + visitorAmount[i + 1]->highestPos()) / 2;
        tmp = v[i] * 2 - tmp;
    }
    tmp = consumption[0]->highestPos();
    for(int i = 0; i < 4; i++) {
        c[i] = (tmp + consumption[i + 1]->highestPos()) / 2;
        tmp = c[i] * 2 - tmp;
    }
    tmp = distance[0]->highestPos();
    for(int i = 0; i < 4; i++) {
        d[i] = (tmp + distance[i + 1]->highestPos()) / 2;
        tmp = d[i] * 2 - tmp;
    }
    return true;
}

bool GlobalStatus::cheat(int *aa, int *bb, int *cc, int *dd, int *ee) {
    for(int i = 0; i < 4; i++) {
        t[i] = aa[i];
        h[i] = bb[i];
        v[i] = cc[i];
        c[i] = dd[i];
        d[i] = ee[i];
    }
    return true;
}

int GlobalStatus::setLevel(const STATUS_ENUM &statusEnum, int parameter) {
    if(statusEnum == Temperature) {
        if(parameter < t[0]) return 1;
        if(parameter < t[1]) return 2;
        if(parameter < t[2]) return 3;
        if(parameter < t[3]) return 4;
        return 5;
    }
    else if(statusEnum == Humidity) {
        if(parameter < h[0]) return 1;
        if(parameter < h[1]) return 2;
        if(parameter < h[2]) return 3;
        if(parameter < h[3]) return 4;
        return 5;
    }
    else if(statusEnum == Consumption) {
        if(parameter < c[0]) return 1;
        if(parameter < c[1]) return 2;
        if(parameter < c[2]) return 3;
        if(parameter < c[3]) return 4;
        return 5;
    }
    else if(statusEnum == VisitorAmount) {
        if(parameter < v[0]) return 1;
        if(parameter < v[1]) return 2;
        if(parameter < v[2]) return 3;
        if(parameter < v[3]) return 4;
        return 5;
    }
    else if(statusEnum == Distance) {
        if(parameter < d[0]) return 1;
        if(parameter < d[1]) return 2;
        if(parameter < d[2]) return 3;
        if(parameter < d[3]) return 4;
        return 5;
    }
};

