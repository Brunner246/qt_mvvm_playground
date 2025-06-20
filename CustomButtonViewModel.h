//
// Created by brunn on 20/06/2025.
//

#ifndef CUSTOMBUTTONVIEWMODEL_H
#define CUSTOMBUTTONVIEWMODEL_H

#include <QString>
#include <functional>

class CustomButtonViewModel {
public:
    CustomButtonViewModel() = default;
    ~CustomButtonViewModel() = default;

    // callbacks
    using TextChangedCallback = std::function<void(const QString&)>;
    using StyleChangedCallback = std::function<void(const QString&)>;

    void setTextChangedCallback(TextChangedCallback callback);
    void setStyleChangedCallback(StyleChangedCallback callback);


#pragma region update-model-notify-observers
    void setText(const QString& text);
    void setStyle(const QString& style);
#pragma endregion update-model-notify-observers

#pragma region event-handlers
    void onClicked();
#pragma endregion event-handlers

private:
    QString m_text;
    QString m_style;

    TextChangedCallback m_textChangedCallback;
    StyleChangedCallback m_styleChangedCallback;

    int m_clickCount = 0;
};

#endif // CUSTOMBUTTONVIEWMODEL_H