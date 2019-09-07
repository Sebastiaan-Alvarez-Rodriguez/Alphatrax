#ifndef RATING_H
#define RATING_H

struct Rating {
    unsigned short userID;
    unsigned short movieID;
    unsigned short rating;
    unsigned timestamp;
};

std::ifstream& operator>>(std::ifstream& in, Rating& r) {
    char c;
    in>>r.userID>>c>>c>>r.movieID>>c>>c>>r.rating>>c>>c>>r.timestamp;
    return in;
}

std::ostream& operator<<(std::ostream& out, Rating& r) {
    out << r.userID<<' '<<r.movieID<<' '<<r.rating<<' '<<r.timestamp<<'\n';
    return out;
}
#endif