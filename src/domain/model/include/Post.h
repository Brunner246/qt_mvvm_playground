//
// Created by brunn on 22/06/2025.
//

#ifndef POST_H
#define POST_H

#include <string>

struct Post {
    int id{};
    int userId{};
    std::string title;
    std::string body;
};

#endif //POST_H
