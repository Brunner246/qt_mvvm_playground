//
// Created by brunn on 22/06/2025.
//

#include "FetchPostUseCase.h"

#include <utility>

FetchPostUseCase::FetchPostUseCase(IPostService *service)
    : m_service(service) {
}

void FetchPostUseCase::execute(const int id, std::function<void(Post)> onSuccess,
                               std::function<void(std::string)> onError) const {
    m_service->fetchPost(id, std::move(onSuccess), std::move(onError));
}
