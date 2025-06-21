//
// Created by brunn on 19/06/2025.
//

#ifndef USERMODEL_H
#define USERMODEL_H
#include <qstring.h>

#include <utility>

struct UserModel {
    QString name;
    QString email;

    explicit UserModel(QString  name = "", QString  email = "")
        : name(std::move(name)), email(std::move(email)) {}

    [[nodiscard]] bool isValid() const {
        return !name.isEmpty() && !email.isEmpty();
    }


};

#endif //USERMODEL_H
