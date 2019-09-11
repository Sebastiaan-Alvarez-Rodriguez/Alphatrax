#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>
#include <limits>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

#include "creator/Creator.h"
#include "ask/Ask.h"

std::vector<Rating> ratings;
std::vector<User> users;
std::vector<Movie> movies;

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

std::vector<Rating> readRatings(std::string r) {    
    std::vector<Rating> return_vector;

    std::ifstream ratings(r);
    Rating ra;
    while (ratings>>ra) {
        return_vector.push_back(ra);
    }
    return return_vector;
}

std::vector<User> readUsers(std::string u) {
    std::vector<User> return_vector;
    std::ifstream users(u);
    User us;
    while (users>>us) {
        return_vector.push_back(us);
    }
    return return_vector;
}

std::vector<Movie> readMovies(std::string m) {
    std::vector<Movie> return_vector;
    std::ifstream movies(m);
    Movie mo;
    while (movies>>mo) {
        return_vector.push_back(mo);
    }
    return return_vector;
}


const std::vector<User> getUsersForMovie(const Movie& movie) {
    std::vector<User> return_vector;
    
    const unsigned short movieID = movie.movieID;

    for (const Rating& r : ratings)
        if (r.movieID == movieID)
            return_vector.push_back(users[r.userID]);//todo: id's == pos?
    return return_vector;
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

    std::cout << "Which movie to predict for?\n";
    auto movie_predict = ask::askMovie(movies);
    auto raters = getUsersForMovie(movie_predict);

    User user;
    if (predictForUser()) {
        user = ask::askUser(users);
        // if () if user picked has rated movie_predict, just return that
    } else {
        user = creator::createUser(users.back().userID+1);
    }
    
    //Predicter
    
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