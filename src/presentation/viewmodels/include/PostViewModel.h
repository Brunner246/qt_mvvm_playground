//
// Created by brunn on 22/06/2025.
//

#pragma once
#include <QObject>
#include <QString>
#include <FetchPostUseCase.h>
#include <viewmodels_export.h>

class VM_API PostViewModel final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString body READ body NOTIFY bodyChanged)

public:
    explicit PostViewModel(FetchPostUseCase *useCase, QObject *parent = nullptr);

    [[nodiscard]] QString title() const;

    [[nodiscard]] QString body() const;

    Q_INVOKABLE void fetchPost(int id);

signals:
    void titleChanged();

    void bodyChanged();

private:
    FetchPostUseCase *m_useCase;
    QString m_title;
    QString m_body;
};
