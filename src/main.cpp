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
#include "container/MTU/MovieToUserContainer.h"
#include "container/UTM/UserToMovieContainer.h"

MovieToUserContainer MTU;
UserToMovieContainer UTM;
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
        -m            path     Location of movies-file

    Optional paramters
        --help
        -h                     Show this panel
)HERE";
}

std::vector<Rating> readRatings(std::string r) {
    std::vector<Rating> ratings;

    std::ifstream file(r);
    Rating ra;
    while (file>>ra)
        ratings.push_back(ra);

    for (const Rating& item : ratings)
        MTU.add(item);
    return ratings;
}

void readUsers(std::string u) {
    std::cout << "Reading users...";
    std::ifstream file(u);
    User us;
    while (file>>us)
        users.insert({us.userID, us});
    std::cout << "Complete!\n";
}

void readMovies(std::string m) {
    std::cout << "Reading movies...";
    std::ifstream file(m);
    Movie mo;
    while (file>>mo)
        movies.insert({mo.movieID, mo});
    std::cout << "Complete!\n";
}

std::unordered_map<unsigned short, unsigned> getDistances(const User& user, const std::unordered_map<unsigned short, Rating>& raters) {
    std::unordered_map<unsigned short, unsigned> distances;
    for (const auto& pair : UTM.find(user)->second) {
        //for each movie where our user has a rating for
        Rating user_r = pair.second;

        Movie cur_movie = movies.find(pair.first)->second;
        //raters = map van alle users voor de to_predict movie naar hun ratings
        for (const auto& it : raters) {
            User cur_user = users.find(it.first)->second;

            auto tmp = UTM.find(cur_user)->second;
            //if cur_user has rated cur_movie too
            if (tmp.find(cur_movie.movieID) != tmp.end()) {
                Rating cur_r = tmp.find(cur_movie.movieID)->second;
                unsigned distance = user_r.rating>cur_r.rating ? user_r.rating-cur_r.rating : cur_r.rating-user_r.rating;
                if (distances.find(cur_user.userID) != distances.end()) {
                    distances[cur_user.userID] += distance;
                    if (distances[cur_user.userID] >= 2)
                        distances[cur_user.userID] -= 2;
                } else {
                    distances[cur_user.userID] = distance + 96;
                }
            }
        }
    }
    return distances;
}

double closeness_users(const User& u1, const User& u2) {
    double oof = 1;
    if (u1.zip == u2.zip)
        oof *= 0.9;
    if (u1.age == u2.age)
        oof *= 0.8;
    if (u1.work == u2.work)
        oof *= 0.9;
    if (u1.gender == u2.gender)
        return oof *= 0.9;
    return oof;
}

void read(std::string u, std::string m) {
    readUsers(u);
    readMovies(m);

}
void run(std::string r) {
    User user = ask::askUser(users);

    std::cout << "Which movie to predict for?\n";
    auto movie_predict = ask::askMovie(movies);

    std::cout << "Reading ratings...";
    std::vector<Rating> ratings = readRatings(r);
    //                 userID
    std::unordered_map<unsigned short, Rating> raters = MTU.find(movie_predict)->second;
    std::cout << "Complete!\n";


    if (raters.find(user.userID) != raters.end()) {
        std::cout << "User has already seen and rated the movie.\n";
        std::cout << "User rated movie " 
        << raters[user.userID].rating << "/5."
        << std::endl;
        return;
    }
    
    for (const Rating& item : ratings) {
        if (raters.find(item.userID) != raters.end())
            UTM.add(item);
        else if (item.userID == user.userID)
            UTM.add(item);
    }

    //Predicter
    //sum algorithm:
    //rating * closeness
    //Getting rating closeness:
    //for each movie where 'user' has a rating for
    //    for each rater of that movie
    //        rater_distance += abs_diff(user.rating, rater.rating)
    //find distance closest to zero

    double predicted_rating = 0;
    size_t group_size = raters.size();
    const auto& distances = getDistances(user, raters);


    unsigned short closest_userID;
    unsigned closest_val = std::numeric_limits<unsigned>::max();
    for (const auto& pair : distances)
        if (pair.second < closest_val) {
            closest_userID = pair.first;
            closest_val = pair.second;
        }
    const User closest_user = users.find(closest_userID)->second;
    std::cout << "Closest user is:\n" << closest_user;
    std::cout << "Distance: " << closest_val << '\n';

    std::cout << "You will like this movie " << MTU.find(movie_predict, closest_user)->second.rating << "/5" << std::endl;
}

int main(int argc, char** argv) {
    std::string ratings_path, users_path, movies_path;

    struct option long_options[] = {
        {"MTU-file", required_argument, NULL, 'r'},
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

    read(users_path, movies_path);
    run(ratings_path);
    return 0;
}