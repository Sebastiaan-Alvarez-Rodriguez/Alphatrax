#ifndef USER_H
#define USER_H

struct User {
    unsigned short userID;
    bool gender; //male = True, female = False
    unsigned short age;
    unsigned short work;
    unsigned int zip;
};

std::ifstream& operator>>(std::ifstream& in, User& u) {
    char c, gen;
    in>>u.userID>>c>>c>>gen>>c>>c>>u.age>>c>>c>>u.work>>c>>c>>u.zip;
    u.gender = gen%2 == 1;
    return in;
}

std::ostream& operator<<(std::ostream& out, User& u) {
    out<<u.userID<<' '<<(u.gender?"male":"female")<<' '<<u.age<<' '<<u.zip<<'\n';
    return out;
}
#endif