#include <fstream>
#include <ostream>
#include "structures/movie/movie.h"

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

std::ostream& operator<<(std::ostream& out, const Movie& m) {
    out<<m.movieID<<'\t'<<m.title<<"\n\t";
    for (Genre g : m.genres)
        out<<' '<< gts(g);
    out<<'\n';
    return out;
}

bool operator==(const Movie& m1, const Movie& m2) {
    return m1.movieID == m2.movieID;
}