//
// Created by 陆逸凡 on 2023/4/2.
//

#include "global_status.h"

GlobalStatus::GlobalStatus() {
    for(int i = 0; i < 4; i++) {
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

int GlobalStatus::highest(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum) const {
    Axis *statusPtr;
    switch(statusEnum) {
        case Temperature:
            statusPtr = temperature[statusDegree];
            return statusPtr->highest();
        case VisitorAmount:
            statusPtr = visitorAmount[statusDegree];
            return statusPtr->highest();
        case Humidity:
            statusPtr = humidity[statusDegree];
            return statusPtr->highest();
        case Consumption:
            statusPtr = consumption[statusDegree];
            return statusPtr->highest();
        case Distance:
            statusPtr = distance[statusDegree];
            return statusPtr->highest();
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

