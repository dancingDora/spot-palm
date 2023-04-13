//
// Created by 陆逸凡 on 2023/3/14.
//

#include "spots.h"

/*
 +------|   |-------|     |--|     |-------|    |      |     +------|
 |              |        |    |        |        |      |     |
 +------+       |       |-----|        |        |      |     +------+
        |       |      |      |        |        |      |            |
 |------+       |     |       |        |        +------+     |------+
 */

Status::Status() {
    temperature = visitorAmount = humidity = consumption = distance = 3;
}

ostream & operator << (ostream &StatusOut, Status &status) {
    StatusOut << "Here temprature is " << status.temperature << '\n';
    StatusOut << "visitor amount is " << status.visitorAmount << '\n';
    StatusOut << "humidity is " << status.humidity << '\n';
    StatusOut << "consumption is " << status.consumption << '\n';
    StatusOut << "distance is " << status.distance << '\n';
    StatusOut << "And these are the whole detailed information of status.\n";
    return StatusOut;
}

/*
 +-----  +-----+   |\     /\   |\    /\   |-----   |\      /  |-------|
 |       |     |   | \   / |   | \  / |   |        | \    |       |
 |       |     |   |  \/   |   |  \/  |   |-----   |  \   |       |
 |       |     |   |       |   |      |   |        |   \  |       |
 +-----  +-----+   |       |   |      |   |-----   |    \/        |
 */
comment::comment(): uid(0), time(0) {
    like = 0;
}

comment::comment(const unsigned &u, const string &n): uid(u), time(0) {
    data = n;
    like = 0;
}

Comments::Comments():size(0){commentsMap.clear();}

void Comments::clear() {
    commentsMap.clear();
    size = 0;
}

unsigned Comments::len() const{
    return size;
}

void Comments::insert(const unsigned &u, const string &s) {
    comment *newComment = new comment(u, s);
    commentsMap.insert(std::pair<unsigned, comment*>(size++, newComment));
}

void Comments::remove(const unsigned &id, const string &s) {
    commentsMap.erase(id);
}

comment* Comments::get(const unsigned &id) {
    return commentsMap[id];
}

comment* &Comments::operator [] (const unsigned &id) {
    return commentsMap[id];
}

bool Comments::addYourLike(const unsigned int &cid) {
    if(commentsMap[cid] == nullptr) {
        cerr << "[spots.cpp/Comments::addYourLike] Invalid add, because commentsMap[" << cid << "] not found.\n";
        return false;
    }
    (commentsMap[cid]->like)++;
    return true;
}
/*
 +-----|    +-----+    +-----+   |-------|
 |          |     |    |     |       |
 +-----+    +-----+    |     |       |
       |    |          |     |       |
 |-----+    |          +-----+       |
 */
Spot::Spot():NS(39.9042), WE(116.4074), province(Beijing), sid(0) {
    status.visitorAmount = status.humidity = status.consumption = status.distance = status.temperature = 3;
}

Spot::Spot(const string &spotNameA, const int &sidA,
     const double &t, const double &v, const double &h, const double &c, const double &d,
     const PROVINCE &provinceA, const string &cityA,
     const double & NSA, const double & WEA)
        : province(provinceA), NS(NSA), WE(WEA), sid(sidA){
    spotName = spotNameA;
    status.temperature = t;
    status.distance = d;
    status.consumption = c;
    status.humidity = h;
    status.visitorAmount = v;
    city = cityA;
}

Spot::Spot(const Spot &s) : province(s.province), NS(s.NS), WE(s.WE), sid(s.sid) {
    spotName = s.spotName;
    status.temperature = s.status.temperature;
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

bool operator < (const Spot &l, const Spot &r) {
    return l.sid < r.sid;
}

bool operator > (const Spot &l, const Spot &r) {
    return l.sid > r.sid;
}
bool operator <= (const Spot &l, const Spot &r) {
    return l.sid <= r.sid;
}

bool operator >= (const Spot &l, const Spot &r) {
    return l.sid >= r.sid;
}

//it should be more strict.
bool operator == (const Spot &l, const Spot &r) {
    return l.sid == r.sid && l.spotName == r.spotName;
}

bool operator != (const Spot &l, const Spot &r) {
    return l.sid != r.sid;
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
    spots.insert(std::pair<int, Spot*>(sidA, newSpot));
    province_spots[provToS(newSpot->province)].push_back(newSpot);
    name_spots.insert(std::pair<string, Spot*>(spotNameA, newSpot));
    return true;
};

bool SpotManager::addSpot(const Spot &spot) {
    if(spots.find(spot.sid) != spots.cend()) {
        cerr << "[SpotManager addSpot(Spot)] Invalid add : " << spot.sid << " exists.\n";
        return false;
    }
    Spot *newSpot = new Spot(spot);
    spots.insert(std::pair<int, Spot*>(spot.sid, newSpot));
    province_spots[provToS(newSpot->province)].push_back(newSpot);
    return true;
};

bool SpotManager::clear() {
    spots.clear();
    province_spots.clear();
    name_spots.clear();
    return true;
}

//s : spot-id   u : user-id   c : comment-id   data : comments.comments[c].data
bool SpotManager::putComment(const unsigned &s, const unsigned int &u, const unsigned int &c, const string &data) {

    // wrong test
    if(spots.find(s) == spots.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find spot : " << s << " does not exist.\n";
        return false;
    }// find the spot
    if(spots[s]->comments.commentsMap.find(c) == spots[s]->comments.commentsMap.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find comment : " << c << " exists.\n";
        return false;
    }// find the comment ( just in spots (map<key : sid, val : Spot*>) )

    //Generate & Put to three maps;
    comment *newComment = new comment(u,data);
    string spotName = spots[s]->spotName;

    spots[s]->comments[c] = newComment;
    string prov = provToS(spots[s]->province);
    for(Spot *it : province_spots[prov])
        if(it == spots[s]) {
            it->comments[c] = newComment;
            break;
        }
    name_spots[spotName]->comments[c] = newComment;

    return true;
}

//s : spot-id   u : user-id   c : comment-id
bool SpotManager::putCommentLike(const unsigned &s, const unsigned &u, const unsigned &c) {

    // wrong test
    if(spots.find(s) == spots.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find spot : " << s << " does not exist.\n";
        return false;
    }// find the spot
    if(spots[s]->comments.commentsMap.find(c) == spots[s]->comments.commentsMap.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find comment : " << c << " exists.\n";
        return false;
    }// find the comment ( just in spots (map<key : sid, val : Spot*>) )

    //Add your treasure like
    spots[s]->comments.addYourLike(c);
}