#include <fstream>
#include <ostream>

#include "structures/rating/rating.h"

std::ifstream& operator>>(std::ifstream& in, Rating& r) {
    char c;
    in>>r.userID>>c>>c>>r.movieID>>c>>c>>r.rating>>c>>c>>r.timestamp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rating& r) {
    out << r.userID<<' '<<r.movieID<<' '<<r.rating<<' '<<r.timestamp<<'\n';
    return out;
}