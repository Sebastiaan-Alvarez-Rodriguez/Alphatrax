#include <unordered_map>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

#include "container/MTU/MovieToUserContainer.h"

void MovieToUserContainer::add(const Rating& r) {
    ratings[r.movieID][r.userID] = r;
}

void MovieToUserContainer::remove(const Rating& r) {
    ratings[r.movieID].erase(r.userID);

    if (ratings[r.movieID].size() == 0)
        ratings.erase(r.movieID);
}

std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator MovieToUserContainer::find(const Movie& m) {
    return ratings.find(m.movieID);
}

std::unordered_map<unsigned short, Rating>::iterator MovieToUserContainer::find(const Movie& m, const User& u) {
    if (find(m) != ratings.end())
        return find(m)->second.find(u.userID);
    throw std::runtime_error("Rating find failure");
}

const std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator MovieToUserContainer::end() {
    return ratings.end();
}