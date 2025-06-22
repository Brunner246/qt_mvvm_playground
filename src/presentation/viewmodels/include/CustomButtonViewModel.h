//
// Created by brunn on 20/06/2025.
//

#ifndef CUSTOMBUTTONVIEWMODEL_H
#define CUSTOMBUTTONVIEWMODEL_H

#include <QString>
#include <functional>
#include <qobjectdefs.h>
#include <QLoggingCategory>
#include <QObject>
#include <unordered_map>
#include <viewmodels_export.h>


Q_DECLARE_LOGGING_CATEGORY(someCategory)

class VM_API CustomButtonViewModel final /*: public QObject*/ {
    Q_GADGET
    // Q_GADGET does not work with VIEWMODELS_EXPORT in msvc
    // Q_GADGET_EXPORT(VIEWMODELS_EXPORT)


public:
    enum CallbackType {
        OnTextChanged,
        OnStyleChanged,
        OnLogging
    };

    Q_ENUM(CallbackType)

    CustomButtonViewModel() = default;

    ~CustomButtonViewModel() = default;

    // callbacks
    using _callback = std::function<void(const QString &)>;

    void registerCallback(CallbackType type, std::function<void(const QString &)> callback);

#pragma region update-model-notify-observers
    void setText(const QString &text);

    void setStyle(const QString &style);
#pragma endregion update-model-notify-observers

#pragma region event-handlers
    void onClicked();
#pragma endregion event-handlers

private:
    QString m_text;
    QString m_style;

    int m_clickCount = 0;
    std::unordered_map<CallbackType, _callback> m_callbacks;
};

#endif // CUSTOMBUTTONVIEWMODEL_H
