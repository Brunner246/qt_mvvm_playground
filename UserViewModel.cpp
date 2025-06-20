//
// Created by brunn on 19/06/2025.
//

#include "UserViewModel.h"
#include "UserModel.h"
#include <QDebug>

UserViewModel::UserViewModel(UserModel* model, QObject* parent)
    : QObject(parent), m_model(model), m_isValid(false) {

    if (m_model) {
        m_name = m_model->name;
        m_email = m_model->email;
        validateInput();
    }
}

QString UserViewModel::name() const {
    return m_name;
}

void UserViewModel::setName(const QString &name) {
    if (m_name == name) {
        return; // No change, no need to emit signal
    }
    m_name = name;
    emit nameChanged(m_name);
}

QString UserViewModel::email() const {
    return m_email;
}

void UserViewModel::setEmail(const QString &email) {
    if (m_email == email) {
        return; // No change, no need to emit signal
    }
    this->m_email = email;
    qDebug() << "Email change received";
    emit emailChanged(m_email);
}

bool UserViewModel::isValid() const {
    return m_isValid;
}

void UserViewModel::save() {
    qDebug() << "Saving user with name:" << m_name << "and email:" << m_email;
    m_model->name = m_name;
    m_model->email = m_email;
    emit saveSucceeded();
}

void UserViewModel::validateInput() {
    if (m_model) {
        m_isValid = m_model->isValid();
        emit isValidChanged(m_isValid);
    }
}
