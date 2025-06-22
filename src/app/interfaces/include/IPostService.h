//
// Created by brunn on 22/06/2025.
//

#pragma once

#include <functional>
#include <string>

struct Post;

class IPostService {
public:
    virtual ~IPostService() = default;

    virtual void fetchPost(int id, std::function<void(Post)> onSuccess, std::function<void(std::string)> onError) = 0;
};
