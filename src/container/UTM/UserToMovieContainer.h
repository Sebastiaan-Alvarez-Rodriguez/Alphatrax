#ifndef USERTOMOVIECONTAINER_H
#define USERTOMOVIECONTAINER_H

#include <unordered_map>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

class UserToMovieContainer {
public:
    void add(const Rating& r);
    void remove(const Rating& r);

    std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator find(const User& u);
    std::unordered_map<unsigned short, Rating>::iterator find(const User& u, const Movie& m);
    const std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator end();

private:
    //                 userID,                            movieID
    std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>> ratings;
};
#endif