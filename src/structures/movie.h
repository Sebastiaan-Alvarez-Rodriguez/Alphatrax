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

std::ifstream& operator>>(std::ifstream& in, Movie &m) {
    m.genres.clear();

    char c;

    in>>m.movieID>>c>>c;

    std::string manual;
    if (!getline(in, manual))
        return in;

    unsigned loc = manual.find("::");
    m.title = manual.substr(0, loc);
    manual = manual.substr(loc+2);

    int sep;
    while ((sep = manual.find("|"))!=-1) {
        m.genres.push_back(stg(manual.substr(0, sep)));
        manual = manual.substr(sep+1);
    }
    m.genres.push_back(stg(manual));
    return in;
}

std::ostream& operator<<(std::ostream& out, Movie& m) {
    out<<m.movieID<<' '<<m.title;
    for (Genre g : m.genres)
        out<<' '<< gts(g);
    out<<'\n';
    return out;
}
#endif