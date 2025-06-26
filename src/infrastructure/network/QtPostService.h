//
// Created by brunn on 22/06/2025.
//

#pragma once

#include <QObject>
#include <IPostService.h>
#include <network_export.h>

class QNetworkAccessManager;
class QNetworkReply;

class NETWORK_API QtPostService final : public QObject, public IPostService {
    Q_OBJECT

public:
    explicit QtPostService(QObject *parent = nullptr);

    void fetchPost(int id,
                   std::function<void(Post)> const &onSuccess,
                   std::function<void(std::string)> const &onError) override;

private slots:
    void handleReply(QNetworkReply *reply) const;

private:
    QNetworkAccessManager* m_manager;
    std::function<void(Post)> m_onSuccess;
    std::function<void(std::string)> m_onError;
};
