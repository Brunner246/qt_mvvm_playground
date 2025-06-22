//
// Created by brunn on 19/06/2025.
//

#ifndef USERVIEWMODEL_H
#define USERVIEWMODEL_H

#include <qobject.h>


struct UserModel;

class UserViewModel final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)

public:
    explicit UserViewModel(UserModel *model, QObject *parent = nullptr);

    [[nodiscard]] QString name() const;

    void setName(const QString &name);

    [[nodiscard]] QString email() const;

    void setEmail(const QString &email);

    [[nodiscard]] bool isValid() const;

public slots:
    void save();

signals:
    void nameChanged(const QString &name);

    void emailChanged(const QString &email);

    void isValidChanged(bool isValid);

    void saveSucceeded();

    void saveFailed(const QString &error);

private:
    void validateInput();

    UserModel *m_model;
    QString m_name;
    QString m_email;
    bool m_isValid;
};

#endif //USERVIEWMODEL_H
