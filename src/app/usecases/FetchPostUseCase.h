//
// Created by brunn on 22/06/2025.
//

#pragma once
#include <uc_export.h>
#include <IPostService.h>

class UC_API FetchPostUseCase {
public:
    explicit FetchPostUseCase(IPostService *service);

    void execute(int id, std::function<void(Post)> onSuccess, std::function<void(std::string)> onError) const;

private:
    IPostService *m_service;
};
