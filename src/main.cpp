#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>

#include "structures/rating.h"
#include "structures/user.h"
#include "structures/movie.h"

static void showHelp(const char *program_name) {
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

static void readRatings(std::string r) {    
    std::ifstream ratings(r);
    Rating ra;
    while (ratings>>ra) {
        // std::cout<<ra;
    }
}

static void readUsers(std::string u) {
    std::ifstream users(u);
    User us;
    while (users>>us) {
        // std::cout<<us;
    }
}

static void readMovies(std::string m) {
    std::ifstream movies(m);
    Movie mo;
    while (movies>>mo) {
        // std::cout<<mo;
    }
}

static void run(std::string r, std::string u, std::string m) {
    std::cout << "Reading ratings...";
    readRatings(r);
    std::cout << " Complete!\nReading users...";
    readUsers(u);
    std::cout << " Complete!\nReading movies...";
    readMovies(m);
    std::cout << " Complete!\n";

}

int main(int argc, char** argv) {
    std::string ratings_path, users_path, movies_path;

    static struct option long_options[] = {
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