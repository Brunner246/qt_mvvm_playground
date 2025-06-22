//
// Created by brunn on 22/06/2025.
//

#include "QtPostService.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <Post.h>


QtPostService::QtPostService(QObject *parent)
: QObject(parent)
, m_manager(new QNetworkAccessManager(this)) {
    //m_manager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
}

void QtPostService::fetchPost(const int id,
                              const std::function<void(Post)> onSuccess,
                              const std::function<void(std::string)> onError) {
    m_onSuccess = onSuccess;
    m_onError = onError;

    const QUrl url(QString("https://jsonplaceholder.typicode.com/posts/%1").arg(id));
    const QNetworkRequest request(url);
    auto *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply);
    });
}

void QtPostService::handleReply(QNetworkReply *reply) const {
    if (reply->error() != QNetworkReply::NoError) {
        m_onError(reply->errorString().toStdString());
        reply->deleteLater();
        return;
    }

    const QByteArray data = reply->readAll();
    const auto json = QJsonDocument::fromJson(data).object();

    Post post;
    post.id = json["id"].toInt();
    post.userId = json["userId"].toInt();
    post.title = json["title"].toString().toStdString();
    post.body = json["body"].toString().toStdString();

    m_onSuccess(post);
    reply->deleteLater();
}
