#include <fstream>
#include <ostream>

#include "structures/user/user.h"

std::ifstream& operator>>(std::ifstream& in, User& u) {
    char c, gen;
    in>>u.userID>>c>>c>>gen>>c>>c>>u.age>>c>>c>>u.work>>c>>c>>u.zip;
    u.gender = gen%2 == 1;
    return in;
}

std::ostream& operator<<(std::ostream& out, const User& u) {
    out<<u.userID<<' '<<(u.gender?"male":"female")<<' '<<u.age<<' '<<u.zip<<'\n';
    return out;
}

bool operator==(const User& u1, const User& u2) {
    return u1.userID == u2.userID;
}