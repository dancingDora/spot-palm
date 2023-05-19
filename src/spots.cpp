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

ostream &operator<<(ostream &StatusOut, Status &status) {
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
comment::comment() : uid(0), time(0) {
    like = 0;
}

comment::comment(const unsigned &u, const string &n) : uid(u), time(0) {
    data = n;
    like = 0;
}

Comments::Comments() : size(0) { commentsMap.clear(); }

void Comments::clear() {
    commentsMap.clear();
    size = 0;
}

unsigned Comments::len() const {
    return size;
}

void Comments::insert(const unsigned &u, const string &s) {
    comment *newComment = new comment(u, s);
    commentsMap.insert(std::pair<unsigned, comment *>(size++, newComment));
}

void Comments::remove(const unsigned &id, const string &s) {
    commentsMap.erase(id);
}

comment *Comments::get(const unsigned &id) {
    return commentsMap[id];
}

comment *&Comments::operator[](const unsigned &id) {
    return commentsMap[id];
}

bool Comments::addYourLike(const unsigned int &cid) {
    if (commentsMap[cid] == nullptr) {
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
Spot::Spot() : NS(39.9042), WE(116.4074), province(Beijing), sid(0),
               image("http://img3m9.ddimg.cn/12/36/1546133799-1_w_1.jpg") {
    status.visitorAmount = status.humidity = status.consumption = status.distance = status.temperature = 3;
}

Spot::Spot(int a, int b) : NS(39.9042), WE(116.4074), province(Beijing), sid(0), test1(a), test2(b),
                           image("http://img3m9.ddimg.cn/12/36/1546133799-1_w_1.jpg") {
    status.visitorAmount = status.humidity = status.consumption = status.distance = status.temperature = 3;
}


Spot::Spot(const string &spotNameA, const int &sidA,
           const double &t, const double &v, const double &h, const double &c, const double &d,
           const PROVINCE &provinceA, const string &cityA,
           const double &NSA, const double &WEA, const string &img)
        : province(provinceA), NS(NSA), WE(WEA), sid(sidA) {
    spotName = spotNameA;
    image = img;
    status.temperature = t;
    status.distance = d;
    status.consumption = c;
    status.humidity = h;
    status.visitorAmount = v;

//    {//for test
//        status._temperature = global_status.setLevel(Temperature, t);
//        status._distance = global_status.setLevel(Distance, d);
//        status._consumption =  global_status.setLevel(Consumption, c);
//        status._humidity =  global_status.setLevel(Humidity, h);
//        status._visitorAmount =  global_status.setLevel(VisitorAmount, v);
//    }
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

ostream &operator<<(ostream &SpotOut, const Spot &spot) {
    SpotOut << "The Spot's spot id : " << spot.sid << '\n';
    SpotOut << "              Name : " << spot.spotName << '\n';
    SpotOut << "in the " << provToS(spot.province) << " , " << spot.city << '\n' << '\n';
    SpotOut << &spot.status;
    return SpotOut;
}

string Spot::to_string() {
    string res = "";
    res += std::to_string(sid) + ' ' + spotName.str() + ' ';
    res += provToS(province) + ' ' + city.str() + ' ';
    res += image + '\n';
    return res;

}

bool operator<(const Spot &l, const Spot &r) {
    return l.sid < r.sid;
}

bool operator>(const Spot &l, const Spot &r) {
    return l.sid > r.sid;
}

bool operator<=(const Spot &l, const Spot &r) {
    return l.sid <= r.sid;
}

bool operator>=(const Spot &l, const Spot &r) {
    return l.sid >= r.sid;
}

//it should be more strict.
bool operator==(const Spot &l, const Spot &r) {
    return l.sid == r.sid && l.spotName == r.spotName;
}

bool operator!=(const Spot &l, const Spot &r) {
    return l.sid != r.sid;
}


SpotManager::SpotManager() {
    spots.clear();
    province_spots.clear();
    spot_num = 0;
}

SpotManager::~SpotManager() {
    spots.clear();
    province_spots.clear();
    name_spots.clear();
}

bool SpotManager::addSpot(const string &spotNameA, const int &sidA,
                          const double &t, const double &v, const double &h, const double &c, const double &d,
                          const PROVINCE &provinceA, const string &cityA,
                          const double &NSA, const double &WEA, const string &img) {
    if (spots.find(sidA) != spots.cend()) {
        cerr << "[SpotManager addSpot(...)] Invalid logout : " << sidA << " exists.\n";
        return 0;
    }
    Spot *newSpot = new Spot(spotNameA, sidA,
                             t, v, h, c, d,
                             provinceA, cityA,
                             NSA, WEA, img);
    newSpot->status._temperature = global_status.setLevel(Temperature, t);
    newSpot->status._distance = global_status.setLevel(Distance, d);
    newSpot->status._consumption =  global_status.setLevel(Consumption, c);
    newSpot->status._humidity =  global_status.setLevel(Humidity, h);
    newSpot->status._visitorAmount =  global_status.setLevel(VisitorAmount, v);
    spots.insert(std::pair<int, Spot *>(sidA, newSpot));
    province_spots[provToS(newSpot->province)].push_back(newSpot);
    name_spots.insert(std::pair<string, Spot *>(spotNameA, newSpot));
    return true;
};

bool SpotManager::addSpot(const Spot &spot) {
    if (spots.find(spot.sid) != spots.cend()) {
        cerr << "[SpotManager addSpot(Spot)] Invalid add : " << spot.sid << " exists.\n";
        return false;
    }
    Spot *newSpot = new Spot(spot);
    spots.insert(std::pair<int, Spot *>(spot.sid, newSpot));
    province_spots[provToS(newSpot->province)].push_back(newSpot);
    return true;
}

bool SpotManager::clear() {
    spots.clear();
    province_spots.clear();
    name_spots.clear();
    return true;
}

//s : spot-id   u : user-id   c : comment-id   data : comments.comments[c].data
bool SpotManager::putComment(const unsigned &s, const unsigned int &u, const unsigned int &c, const string &data) {

    // wrong test
    if (spots.find(s) == spots.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find spot : " << s << " does not exist.\n";
        return false;
    }// find the spot
    if (spots[s]->comments.commentsMap.find(c) == spots[s]->comments.commentsMap.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find comment : " << c << " exists.\n";
        return false;
    }// find the comment ( just in spots (map<key : sid, val : Spot*>) )

    //Generate & Put to three maps;
    comment *newComment = new comment(u, data);
    string spotName = spots[s]->spotName;

    spots[s]->comments[c] = newComment;
    string prov = provToS(spots[s]->province);
    for (Spot *it: province_spots[prov])
        if (it == spots[s]) {
            it->comments[c] = newComment;
            break;
        }
    name_spots[spotName]->comments[c] = newComment;

    return true;
}

//s : spot-id   u : user-id   c : comment-id
bool SpotManager::putCommentLike(const unsigned &s, const unsigned &u, const unsigned &c) {

    // wrong test
    if (spots.find(s) == spots.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find spot : " << s << " does not exist.\n";
        return false;
    }// find the spot
    if (spots[s]->comments.commentsMap.find(c) == spots[s]->comments.commentsMap.cend()) {
        cerr << "[SpotManager Put Comment] Invalid : find comment : " << c << " exists.\n";
        return false;
    }// find the comment ( just in spots (map<key : sid, val : Spot*>) )

    //Add your treasure like
    spots[s]->comments.addYourLike(c);
    return true;
}

string SpotManager::fuzzyReco(const int &a, const int &b, const int &c, const int &d, const int &e) {
    /*
     * a is temperature
     * b is visitorAmount
     * c is humidity
     * d is consumption
     * e is distance
     */
    string res = "";
    std::unordered_map<int, vector<unsigned>> rank;
    vector<unsigned> recoRes;

    rank.clear();
    recoRes.clear();

    int len = spots.size();
    int temscore, visscore, humscore, conscore, disscore, allscore;
    int cnt = !!a + !!b + !!c + !!d + !!e;
    Spot *temp = new Spot();
    int max = -1;
    // 算出景点的分数，加入到rank数组里
    for (int i = 0; i < len; i++) {
        temp = spots[i];
        temscore = score(a, temp->status._temperature);
        visscore = score(b, temp->status._visitorAmount);
        humscore = score(c, temp->status._humidity);
        conscore = score(d, temp->status._consumption);
        disscore = score(e, temp->status._distance);

        allscore = ((temscore + visscore + humscore + conscore + disscore) / cnt) * 5;
        if (allscore >= 60){
            max = std::max(max, allscore);
            rank[allscore].push_back(i);
//            cout<<i<<'\n';
        }

        //fuzzy_reco -t 1 -h 1 -v 1 -c 1 -d 1
    }


    // 根据rank数组的值将对应的spot加入result数组里（按分数的降序排列）
    for (auto it = rank.begin(); it != rank.end(); it++) {
//        cerr << it->first << '\n';
        for ( int i = 0; i < it->second.size();i++) {
            recoRes.push_back(it->second[i]);
//            cerr << *it2 << ' ';
        }
//        cout << '\n';
    }
    for (int i = recoRes.size() - 1; i >= 0; i--)
        res += spots[recoRes[i]]->to_string();
//    cout << res << "\n\n";
    return res;
}
