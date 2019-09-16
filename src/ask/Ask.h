#ifndef ASK_H
#define ASK_H

#include <set>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

namespace ask {
    bool askGender();
    unsigned short askAge();
    unsigned short askWork();
    std::string askZip();
    const std::set<Rating> askRatings(const std::unordered_map<unsigned short, Movie>& options);
    unsigned short askRating();
    bool predictForUser();

    const User askUser(const std::unordered_map<unsigned short, User>& options);
    const Movie askMovie(const std::unordered_map<unsigned short, Movie>& options);
}
#endif