#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <numeric>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

#include "creator/Creator.h"
#include "ask/Ask.h"
#include "container/RatingContainer.h"

RatingContainer ratings;
std::unordered_map<unsigned short, User> users;
std::unordered_map<unsigned short, Movie> movies;

void showHelp(const char *program_name) {
    std::cout << program_name << " [-r <path> -u <path> -m <path>] [-h]" << std::endl;
    std::cout << R"HERE(
    Required parameters
        --ratings-file
        -r            path     Location of ratings-file
        --users-file
        -u            path     Location of users-file
        --movies-file
        -m            path     Location of users-file

    Optional paramters
        --help
        -h                     Show this panel
)HERE";
}

RatingContainer readRatings(std::string r) {    
    RatingContainer return_map;
    std::vector<Rating> tmp;

    std::ifstream ratings(r);
    Rating ra;
    while (ratings>>ra)
        tmp.push_back(ra);
    for (auto item : tmp)
        return_map.add(item);
    return return_map;
}

std::unordered_map<unsigned short, User> readUsers(std::string u) {
    std::unordered_map<unsigned short, User> return_map;
    std::ifstream users(u);
    User us;
    while (users>>us)
        return_map.insert({us.userID, us});
    return return_map;
}

std::unordered_map<unsigned short, Movie> readMovies(std::string m) {
    std::unordered_map<unsigned short, Movie> return_map;
    std::ifstream movies(m);
    Movie mo;
    while (movies>>mo)
        return_map.insert({mo.movieID, mo});
    return return_map;
}

bool predictForUser() {
    unsigned short option = 0;
    do {
        if (option > 1)
            std::cout << "Please choose 0 or 1.\n";
        std::cout << "Choose a user to predict for[0], ";
        std::cout << "or give your own input[1]?\n";
        std::cin >> option;
    } while(option > 1);
    return option == 0;
}

void run(std::string r, std::string u, std::string m) {
    std::cout << "Reading ratings...";
    ratings = readRatings(r);
    std::cout << " Complete!\nReading users...";
    users = readUsers(u);
    std::cout << " Complete!\nReading movies...";
    movies = readMovies(m);
    std::cout << " Complete!\n";

    User user;
    if (predictForUser())
        user = ask::askUser(users);
    else
        user = creator::createUser(std::numeric_limits<unsigned short>::max());
    
    std::cout << "Which movie to predict for?\n";
    auto movie_predict = ask::askMovie(movies);
    std::unordered_map<unsigned short, Rating> raters = ratings.find(movie_predict)->second; //map: uID -> rating

    if (raters.find(user.userID) != raters.end()) {
        std::cout << "User has already seen and rated the movie.\n";
        std::cout << "User rated movie " 
        << raters[user.userID].rating << "/5."
        << std::endl;
        return;
    }
    

    //Predicter
    double predicted_rating = 0;
    size_t group_size = raters.size();
    for (auto pair : raters) {
        User u = users.find(pair.first)->second;
        Rating r = pair.second;
    }
}

int main(int argc, char** argv) {
    std::string ratings_path, users_path, movies_path;

    struct option long_options[] = {
        {"ratings-file", required_argument, NULL, 'r'},
        {"users-file", required_argument, NULL, 'u'},
        {"movies-file", required_argument, NULL, 'm'},
        {"help", no_argument, NULL, 'h'}
    };

    const char* program_name = argv[0];
    int c;
    if (argc != 7) {
        showHelp(program_name);
        return 0;
    }
    while ((c = getopt_long(argc, argv, "r:u:m:h", long_options, NULL)) != -1) {
        switch (c) {
            case 'r':
                ratings_path = optarg;
                break;
            case 'u':
                users_path = optarg;
                break;
            case 'm':
                movies_path = optarg;
                break;
            case 'h':
            default:
                showHelp(program_name);
                return 0;
        }
    }
    argc -= optind;
    argv += optind;

    run(ratings_path, users_path, movies_path);
    return 0;
}