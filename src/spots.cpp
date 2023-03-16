//
// Created by 陆逸凡 on 2023/3/14.
//

#include "spots.h"

Status::Status() {
    temp = visitorAmount = humidity = consumption = distance = 3;
}

ostream & operator << (ostream &StatusOut, Status &status) {
    StatusOut << "Here temprature is " << status.temp << '\n';
    StatusOut << "visitor amount is " << status.visitorAmount << '\n';
    StatusOut << "humidity is " << status.humidity << '\n';
    StatusOut << "consumption is " << status.consumption << '\n';
    StatusOut << "distance is " << status.distance << '\n';
    StatusOut << "And these are the whole detailed information of status.\n";
    return StatusOut;
}

comment::comment(): uid(0), time(0) {
    like = 0;
}

comment::comment(const unsigned &u, const string &n): uid(u), time(0) {
    data = n;
    like = 0;
}

Comments::Comments():size(0){comments.clear();}

void Comments::clear() {
    comments.clear();
    size = 0;
}

unsigned Comments::len() const{
    return size;
}

void Comments::insert(const unsigned &u, const string &s) {
    comment *newComment = new comment(u, s);
    comments.insert(std::pair<unsigned, comment>(size++, *newComment));
}

void Comments::remove(const unsigned &id, const string &s) {
    comments.erase(id);
}

comment Comments::get(const unsigned &id) {
    return comments[id];
}
comment &Comments::operator [] (const unsigned &id) {
    return comments[id];
}

Spot::Spot():NS(39.9042), WE(116.4074), province(Beijing), sid(0) {
    status.visitorAmount = status.humidity = status.consumption = status.distance = status.temp = 3;
}

Spot::Spot(const string &spotNameA, const int &sidA,
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

Spot::Spot(const Spot &s) : province(s.province), NS(s.NS), WE(s.WE), sid(s.sid) {
    spotName = s.spotName;
    status.temp = s.status.temp;
    status.distance = s.status.distance;
    status.consumption = s.status.consumption;
    status.humidity = s.status.humidity;
    status.visitorAmount = s.status.visitorAmount;
    city = s.city;
}

ostream& operator << (ostream &SpotOut, const Spot &spot) {
    SpotOut << "The Spot's spot id : " << spot.sid << '\n';
    SpotOut << "              Name : " << spot.spotName << '\n';
    SpotOut << "in the " << provToS(spot.province) << " , " << spot.city << '\n' << '\n';
    SpotOut <<  &spot.status;
    return SpotOut;
}

SpotManager::SpotManager() {
    spots.clear();
    province_spots.clear();
}

SpotManager::~SpotManager() {
    spots.clear();
    province_spots.clear();
    name_spots.clear();
}

bool SpotManager::addSpot(const string &spotNameA, const int &sidA,
             const double &t, const double &v, const double &h, const double &c, const double &d,
             const PROVINCE &provinceA, const string &cityA,
             const double & NSA, const double & WEA) {
    if(spots.find(sidA) != spots.cend()) {
        cerr << "[SpotManager addSpot(...)] Invalid logout : " << sidA << " exists.\n";
        return 0;
    }
    Spot *newSpot = new Spot(spotNameA, sidA,
                             t,v,h,c,d,
                             provinceA, cityA,
                             NSA, WEA);
    spots.insert(std::pair<int, Spot>(sidA, *newSpot));
    province_spots[provToS(newSpot->province)].push_back(*newSpot);
    name_spots.insert(std::pair<string, Spot>(spotNameA, *newSpot));
    return true;
};

bool SpotManager::addSpot(const Spot &spot) {
    if(spots.find(spot.sid) != spots.cend()) {
        cerr << "[SpotManager addSpot(Spot)] Invalid logout : " << spot.sid << " exists.\n";
        return false;
    }
    Spot *newSpot = new Spot(spot);
    spots.insert(std::pair<int, Spot>(spot.sid, *newSpot));
    province_spots[provToS(newSpot->province)].push_back(*newSpot);
    return true;
};

bool SpotManager::clear() {
    spots.clear();
    province_spots.clear();
    name_spots.clear();
    return true;
}