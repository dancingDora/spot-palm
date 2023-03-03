//
// Created by 陆逸凡 on 2023/3/3.
//
#include <iostream>
#include <cmath>

const double EARTH_RADIUS = 6371.0; // 地球平均半径，单位为公里

// 将角度转换为弧度
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

// 计算两个经纬度坐标之间的距离，单位为公里
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

int main() {
    double lat1 = 31.2304; // 第一个点的纬度
    double lon1 = 121.4737; // 第一个点的经度

    double lat2 = 39.9042; // 第二个点的纬度
    double lon2 = 116.4074; // 第二个点的经度

    double dist = distance(lat1, lon1, lat2, lon2); // 计算两点之间的距离

    std::cout << "Distance between the two points is " << dist << " km." << std::endl;

    return 0;
}
