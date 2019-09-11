#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

#include "enums/genre.h"

struct Movie {
    unsigned short movieID;
    std::string title;
    std::vector<Genre> genres;
};

std::ifstream& operator>>(std::ifstream& in, Movie &m);
std::ostream& operator<<(std::ostream& out, const Movie& m);
bool operator==(const Movie& m1, const Movie& m2);
#endif