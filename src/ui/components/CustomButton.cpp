//
// Created by brunn on 20/06/2025.
//

#include "CustomButton.h"

CustomButton::CustomButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent) {
    initializeStyle();
}

CustomButton::CustomButton(QWidget* parent)
    : QPushButton(parent)
{
    initializeStyle();
}

QString CustomButton::defaultStyle() {
    return "QPushButton {"
           "    background-color: #4a86e8;"
           "    color: white;"
           "    border-radius: 6px;"
           "    padding: 8px 16px;"
           "    font-size: 14px;"
           "    font-weight: bold;"
           "}"
           "QPushButton:hover {"
           "    background-color: #3a76d8;"
           "}"
           "QPushButton:pressed {"
           "    background-color: #2a66c8;"
           "}";
}

void CustomButton::initializeStyle() {
    setStyleSheet(defaultStyle());
    setCursor(Qt::PointingHandCursor);
    setMinimumSize(100, 30);
}
