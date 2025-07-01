//
// Created by MichaelBrunner on 01/07/2025.
//

#pragma once

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MyTreeView; }
QT_END_NAMESPACE

class QStandardItemModel;

class MyTreeView final: public QWidget {
Q_OBJECT

public:
    explicit MyTreeView(QWidget *parent = nullptr);
    ~MyTreeView() override;

private slots:
    void onItemClicked(const QModelIndex &index) const;

private:
    Ui::MyTreeView *ui;
    QStandardItemModel* m_model{nullptr};
};
