//
// Created by 陆逸凡 on 2023/4/2.
//

#ifndef SPOT_PALM_QUESTIONARE_H
#define SPOT_PALM_QUESTIONARE_H

#include <iostream>
#include "util/tools.h"

class GlobalStatus {

public:

    Axis *temperature[5];
    Axis *visitorAmount[5];
    Axis *humidity[5];
    Axis *consumption[5];
    Axis *distance[5];

public:

    bool questionnaire();

    GlobalStatus();

    bool modifyStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval);

    int highest(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum) const;

private:

    bool addStatus(const STATUS_DEGREE &statusDegree, const STATUS_ENUM &statusEnum, const Interval &interval);


};


#endif //SPOT_PALM_QUESTIONARE_H
