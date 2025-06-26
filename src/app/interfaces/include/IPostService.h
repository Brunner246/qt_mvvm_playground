//
// Created by brunn on 22/06/2025.
//

#pragma once

#include <functional>
#include <string>

struct Post;

class __declspec(dllexport) IPostService
{
public:
    virtual ~IPostService() = default;

    virtual void fetchPost(int id,
                           std::function<void(Post)> const &onSuccess,
                           std::function<void(std::string)> const &onError) = 0;
};
