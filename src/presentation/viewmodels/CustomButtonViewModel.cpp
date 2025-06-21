//
// Created by brunn on 20/06/2025.
//

#include "include/CustomButtonViewModel.h"
#include <QDebug>
#include <utility>

Q_LOGGING_CATEGORY(someCategory, "someCategory.CustomButtonViewModel")

void CustomButtonViewModel::registerCallback(const CallbackType type, std::function<void(const QString &)> callback) {
    m_callbacks[type] = std::move(callback);
}

void CustomButtonViewModel::setText(const QString &text) {
    if (m_text == text) return;
    m_text = text;

    if (m_callbacks.contains(CustomButtonViewModel::OnTextChanged)) {
        m_callbacks[OnTextChanged](m_text);
    }
    if (m_callbacks.contains(CustomButtonViewModel::OnLogging)) {
        m_callbacks[OnLogging](QString("LOG: Text changed to: %1").arg(m_text));
    }
}

void CustomButtonViewModel::setStyle(const QString &style) {
    if (m_style == style) return;

    m_style = style;
    if (m_callbacks.contains(CustomButtonViewModel::OnStyleChanged)) {
        m_callbacks[OnStyleChanged](m_style);
    }
    if (m_callbacks.contains(CustomButtonViewModel::OnLogging)) {
        m_callbacks[OnLogging](QString("LOG: Style changed"));
    }
}

void CustomButtonViewModel::onClicked() {
    m_clickCount++;
    qCDebug(someCategory) << "Button clicked" << m_clickCount << "times";

    setText(QString("Clicked %1 times").arg(m_clickCount));
    if (m_callbacks.contains(CustomButtonViewModel::OnLogging)) {
        m_callbacks[OnLogging](QString("LOG: Button clicked %1 times").arg(m_clickCount));
    }
}
