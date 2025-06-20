//
// Created by brunn on 20/06/2025.
//

#include "CustomButtonViewModel.h"
#include <QDebug>

void CustomButtonViewModel::setTextChangedCallback(TextChangedCallback callback) {
    m_textChangedCallback = std::move(callback);
}

void CustomButtonViewModel::setStyleChangedCallback(StyleChangedCallback callback) {
    m_styleChangedCallback = std::move(callback);
}

void CustomButtonViewModel::setText(const QString& text) {
    if (m_text != text) {
        m_text = text;
        if (m_textChangedCallback) {
            m_textChangedCallback(m_text);
        }
    }
}

void CustomButtonViewModel::setStyle(const QString& style) {
    if (m_style != style) {
        m_style = style;
        if (m_styleChangedCallback) {
            m_styleChangedCallback(m_style);
        }
    }
}

void CustomButtonViewModel::onClicked() {
    m_clickCount++;
    qDebug() << "Button clicked" << m_clickCount << "times";

    setText(QString("Clicked %1 times").arg(m_clickCount));
}