//
// Created by brunn on 20/06/2025.
//

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QString>
#include <QObject>

class CustomButton final : public QPushButton {
    Q_OBJECT

public:
    explicit CustomButton(const QString& text, QWidget* parent = nullptr);
    ~CustomButton() override = default;

    static QString defaultStyle();

private:
    void initializeStyle();
};

#endif // CUSTOMBUTTON_H
