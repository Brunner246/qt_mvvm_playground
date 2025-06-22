//
// Created by brunn on 22/06/2025.
//

#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>


class CustomButtonViewModel;

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog final : public QMainWindow {
Q_OBJECT

public:
    explicit Dialog(CustomButtonViewModel* viewModel, QWidget *parent = nullptr);
    ~Dialog() override;

private:
    Ui::Dialog *ui;
    CustomButtonViewModel* m_viewModel;
};


#endif //DIALOG_H
