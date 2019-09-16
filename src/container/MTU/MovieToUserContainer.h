#ifndef MOVIETOUSERCONTAINER_H
#define MOVIETOUSERCONTAINER_H

#include <unordered_map>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

class MovieToUserContainer {
public:
    void add(const Rating& r);
    void remove(const Rating& r);

    std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator find(const Movie& m);
    std::unordered_map<unsigned short, Rating>::iterator find(const Movie& m, const User& u);
    const std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator end();

private:
    //                 movieID,                           userID
    std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>> ratings;
};
#endif