//
// Created by MichaelBrunner on 30/06/2025.
//

#pragma once

#include <user_interface_export.h>

class UI_API ConfigDialogBase
{
public:
    virtual ~ConfigDialogBase() = default;

protected:
    virtual void setupUI() = 0;
    virtual void setupConnections() = 0;
    virtual bool validateInput() = 0;
};
