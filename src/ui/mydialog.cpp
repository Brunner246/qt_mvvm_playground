//
// Created by MichaelBrunner on 01/07/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyDialog.h" resolved

#include "mydialog.h"

#include "mytreeview.h"
#include "ui_MyDialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    initialize();
}

void MyDialog::initialize()
{
    this->setupUI();
    this->setupConnections();
}

MyDialog::~MyDialog()
{
    delete ui;
}

bool MyDialog::validateInput()
{
    return true;
}

void MyDialog::setupUI()
{
    ui->leftLayout->addWidget(new MyTreeView(this));
}

void MyDialog::setupConnections()
{
}
