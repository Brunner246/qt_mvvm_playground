//
// Created by brunn on 22/06/2025.
//

#include "include/PostViewModel.h"
#include <Post.h>

PostViewModel::PostViewModel(FetchPostUseCase *useCase, QObject *parent)
    : QObject(parent), m_useCase(useCase) {
}

QString PostViewModel::title() const { return m_title; }
QString PostViewModel::body() const { return m_body; }

void PostViewModel::fetchPost(const int id) {
    m_useCase->execute(id,
                       [this](const Post &post) {
                           m_title = QString::fromStdString(post.title);
                           m_body = QString::fromStdString(post.body);
                           emit titleChanged();
                           emit bodyChanged();
                       },
                       [this](const std::string &error) {
                           m_title = "Error";
                           m_body = QString::fromStdString(error);
                           emit titleChanged();
                           emit bodyChanged();
                       });
}
