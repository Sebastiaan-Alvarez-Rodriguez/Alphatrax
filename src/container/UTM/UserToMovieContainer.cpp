#include <unordered_map>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"
#include "container/UTM/UserToMovieContainer.h"

void UserToMovieContainer::add(const Rating& r) {
    ratings[r.userID][r.movieID] = r;
}

void UserToMovieContainer::remove(const Rating& r) {
    ratings[r.userID].erase(r.movieID);

    if (ratings[r.userID].size() == 0)
        ratings.erase(r.userID);
}

std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator UserToMovieContainer::find(const User& u) {
    return ratings.find(u.userID);
}

std::unordered_map<unsigned short, Rating>::iterator UserToMovieContainer::find(const User& u, const Movie& m) {
    if (find(u) != ratings.end())
        return find(u)->second.find(m.movieID);
    throw std::runtime_error("Rating find failure");
}

const std::unordered_map<unsigned short, std::unordered_map<unsigned short, Rating>>::iterator UserToMovieContainer::end() {
    return ratings.end();
}