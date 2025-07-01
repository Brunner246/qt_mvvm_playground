//
// Created by brunn on 22/06/2025.
//

#include "CprPostService.h"
#include <cpr/cpr.h>
#include <QJsonDocument>
#include <QJsonObject>


void CprPostService::fetchPost(const int id,
                               const std::function<void(Post)> &onSuccess,
                               const std::function<void(std::string)> &onError)
{
    const std::string url = "https://jsonplaceholder.typicode.com/posts/" + std::to_string(id);

    const cpr::Response response = cpr::Get(cpr::Url{url});

    if (response.status_code != 200) {
        onError("Error: " + std::to_string(response.status_code) + " - " + response.error.message);
        return;
    }

    try {
        const Post post = parsePostFromJson(response.text);
        onSuccess(post);
    }
    catch (const std::exception &e) {
        onError(std::string("JSON parsing error: ") + e.what());
    }
}

Post CprPostService::parsePostFromJson(const std::string &jsonData)
{
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(jsonData));

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        throw std::runtime_error("Invalid JSON data");
    }

    QJsonObject jsonObj = jsonDoc.object();

    Post post;
    post.id = jsonObj["id"].toInt();
    post.userId = jsonObj["userId"].toInt();
    post.title = jsonObj["title"].toString().toStdString();
    post.body = jsonObj["body"].toString().toStdString();
    return post;
}
