#ifndef USER_H
#define USER_H

#include <string>

struct User {
    unsigned short userID;
    bool gender; //male = True, female = False
    unsigned short age;
    unsigned short work;
    std::string zip;
};
std::ifstream& operator>>(std::ifstream& in, User& u);
std::ostream& operator<<(std::ostream& out, const User& u);
#endif