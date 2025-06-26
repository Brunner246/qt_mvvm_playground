//
// Created by brunn on 22/06/2025.
//

#ifndef CPRPOSTSERVICE_H
#define CPRPOSTSERVICE_H

#include <functional>
#include <string>
#include <Post.h>
#include <network_export.h>
#include "IPostService.h"

class NETWORK_API CprPostService final: public IPostService
{
public:
    CprPostService() = default;
    ~CprPostService() override = default;

    void fetchPost(int id,
            const std::function<void(Post)> &onSuccess,
            const std::function<void(std::string)> &onError) override;

private:
    [[nodiscard]] static Post parsePostFromJson(const std::string &jsonData);


};

#endif //CPRPOSTSERVICE_H
