#ifndef ASK_H
#define ASK_H

#include <vector>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

namespace ask {
    bool askGender();
    unsigned short askAge();
    unsigned short askWork();
    std::string askZip();
    const std::vector<Rating> askRatings(const std::vector<Movie>& options);
    unsigned short askRating();

    const User askUser(const std::vector<User>& options);
    const Movie askMovie(const std::vector<Movie>& options);
}
#endif