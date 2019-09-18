#ifndef GENRE_H
#define GENRE_H
#include <string>
#include <unordered_map>

enum Genre {
    Action,
    Adventure,
    Animation,
    Children,
    Comedy,
    Crime,
    Documentary,
    Drama,
    Fantasy,
    FilmNoir,
    Horror,
    Musical,
    Mystery,
    Romance,
    SciFi,
    Thriller,
    War,
    Western
};

inline Genre stg(const std::string& s) {
    const static std::unordered_map<std::string, Genre> string_to_genre = 
    {{"Action",Action},
    {"Adventure",Adventure},
    {"Animation",Animation},
    {"Children's",Children},
    {"Comedy",Comedy},
    {"Crime",Crime},
    {"Documentary",Documentary},
    {"Drama",Drama},
    {"Fantasy",Fantasy},
    {"Film-Noir",FilmNoir},
    {"Horror",Horror},
    {"Musical",Musical},
    {"Mystery",Mystery},
    {"Romance",Romance},
    {"Sci-Fi",SciFi},
    {"Thriller",Thriller},
    {"War",War},
    {"Western",Western}};

    return string_to_genre.find(s)->second;
}

inline const std::string& gts(const Genre& g) {
    const static std::unordered_map<int, std::string> genre_to_string = 
    {{Action,"Action"},
    {Adventure,"Adventure"},
    {Animation,"Animation"},
    {Children,"Children"},
    {Comedy,"Comedy"},
    {Crime,"Crime"},
    {Documentary,"Documentary"},
    {Drama,"Drama"},
    {Fantasy,"Fantasy"},
    {FilmNoir,"FilmNoir"},
    {Horror,"Horror"},
    {Musical,"Musical"},
    {Mystery,"Mystery"},
    {Romance,"Romance"},
    {SciFi,"SciFi"},
    {Thriller,"Thriller"},
    {War,"War"},
    {Western,"Western}"}};

    return genre_to_string.find(g)->second;
}
#endif
