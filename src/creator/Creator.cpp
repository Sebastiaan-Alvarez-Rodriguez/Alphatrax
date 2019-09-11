#include "structures/user/user.h"

#include "ask/Ask.h"
#include "creator/Creator.h"

namespace creator {

    const User createUser(unsigned short free_id) {
        User u;
        u.userID = free_id;
        u.gender = ask::askGender();
        u.age = ask::askAge();
        u.work = ask::askWork();
        u.zip = ask::askZip();
        return u;
    }
}