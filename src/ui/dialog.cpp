//
// Created by brunn on 22/06/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Dialog.h" resolved

#include "dialog.h"
#include "ui_Dialog.h"
#include "CustomButtonViewModel.h"

Dialog::Dialog(CustomButtonViewModel *viewModel, QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::Dialog)
      , m_viewModel(viewModel) {
    if (!m_viewModel) {
        qWarning() << "ViewModel is null, creating a new instance.";
        throw std::runtime_error("ViewModel cannot be null");
    }
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}
