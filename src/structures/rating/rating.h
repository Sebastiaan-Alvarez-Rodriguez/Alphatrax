#ifndef RATING_H
#define RATING_H

#include "structures/rating/rating.h"

struct Rating {
    unsigned short userID;
    unsigned short movieID;
    unsigned short rating;
    unsigned timestamp;
};
std::ifstream& operator>>(std::ifstream& in, Rating& r);
std::ostream& operator<<(std::ostream& out, const Rating& r);
#endif