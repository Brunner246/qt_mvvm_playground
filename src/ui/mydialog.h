//
// Created by MichaelBrunner on 01/07/2025.
//

#pragma once

#include <QDialog>
#include  <user_interface_export.h>
#include "ConfigDialogBase.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
class MyDialog;
}

QT_END_NAMESPACE

class UI_API MyDialog: public QDialog, public ConfigDialogBase
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    void initialize();

    ~MyDialog() override;

protected:
    bool validateInput() override;
    void setupUI() override;
    void setupConnections() override;

private:
    Ui::MyDialog *ui{nullptr};
};
