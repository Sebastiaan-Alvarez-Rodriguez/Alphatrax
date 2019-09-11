#include <string>
#include <unordered_map>
#include <limits>
#include <iostream>
#include <algorithm>

#include "structures/rating/rating.h"
#include "structures/user/user.h"
#include "structures/movie/movie.h"

#include "ask/Ask.h"

namespace ask {
    const User askUser(const std::vector<User>& options) {
        for (const User& option : options)
            std::cout << option;
        std::cout << "Please select a user ID to predict for.\n";

        unsigned short chosen_id;
         do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (chosen_id > options.back().userID)
                std::cout << "No such id" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> chosen_id;
        } while (!std::cin.good() || chosen_id > options.back().userID);
        return options[chosen_id];
    }

    const Movie askMovie(const std::vector<Movie>& options) {
        std::cout << "Please select a movie.\nOptions:";
        std::cout << "id\ttitle (genre(s) below each entry)\n";
        for (const Movie& movie : options)
            std::cout << movie;
        std::cout << "Please type the id of the movie: ";

        unsigned short chosen_id;
        do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (chosen_id > options.back().movieID)
                std::cout << "No such id" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> chosen_id;
        } while (!std::cin.good() || chosen_id > options.back().movieID);
        return options[chosen_id];
    }

    unsigned short askRating() {
        std::cout<<"On a range of [1-5] (inclusive), how well did you like this movie?"<<std::endl;
        unsigned short r;
        do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (r < 1 || r > 5)
                std::cout << "Ratings must be between 1 and 5 (inclusive)" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> r;
        } while (!std::cin.good() || r < 1 || r > 5);
        return r;
    }

    const std::vector<Rating> askRatings(const std::vector<Movie>& options) {
        std::vector<Rating> ratings;
        std::vector<Movie> local_options = options;
        bool done = false;
        std::cout << "Provide some ratings, so we can run our algorithm." << std::endl;
        while (!done) {
            std::cout << "Provide a rating for which movie?" << std::endl;
            auto movie = askMovie(local_options);
            Rating r;
            r.movieID = movie.movieID;
            r.rating = askRating();
            ratings.push_back(r);
            std::remove(local_options.begin(), local_options.end(), movie);
            
            std::cout << "Another movie? [Y/n]" << std::endl;
            char c;
            std::cin >> c;
            if (c != 'Y' && c != 'y')
                done = true;
        }
        return ratings;
    }

    bool askGender() {
        unsigned short choice = 0;
        std::cout << "What is your gender? Female[0] or Male[1]?" << std::endl;
        do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (choice > 1)
                std::cout << "Type 0 or 1." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> choice;
        } while (!std::cin.good() || choice > 1);
        return choice == 1;
    }

    unsigned short askAge() {
        unsigned short choice = 0;
        std::cout << "What is your age? Options:\n";
        std::cout << "[0] <18\n[1] 18-24\n[2] 25-34\n[3] 35-44\n";
        std::cout << "[4] 45-49\n[5] 50-55\n[6] 56+\n";
        do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (choice > 6)
                std::cout << "Type a number between 0 and 6 (inclusive)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> choice;
        } while (!std::cin.good() || choice > 6);
        
        std::unordered_map<unsigned short, unsigned short> translate =
            {{0, 1}, {1, 18}, {2, 25}, {3, 35}, {4, 45}, {5, 50}, {6, 56}};
        return translate[choice];
    }

    unsigned short askWork() {
        unsigned short choice = 0;
        std::cout << "What type of work do you perform? Options:\n" << std::endl;
        std::cout << "[0] other (or not specified)\n";
        std::cout << "[1] academic/educator\n[2] artist\n";
        std::cout << "[3] clerical/admin\n[4] college/grad student\n";
        std::cout << "[5] customer service\n[6] doctor/health care\n";
        std::cout << "[7] executive/managerial\n[8] farmer\n[9] homemaker\n";
        std::cout << "[10] K-12 student\n[11] lawyer\n[12] programmer\n";
        std::cout << "[13] retired\n[14] sales/marketing\n[15] scientist\n";
        std::cout << "[16] self-employed\n[17] technician/engineer\n";
        std::cout << "[18] tradesman/craftsman\n[19] unemployed\n[20] writer\n";

        do {
            if (!std::cin.good())
                std::cout << "Type a valid number" << std::endl;
            else if (choice > 20)
                std::cout << "Type a number between 0 and 20 (inclusive)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<unsigned>::max(), '\n');
            std::cin >> choice;
        } while (!std::cin.good() || choice > 20);
        return choice;
    }

    std::string askZip() {
        std::cout << "Please type your zip code: " << std::endl;
        std::string choice;
        std::cin >> choice;
        return choice;
    }
}