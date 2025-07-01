//
// Created by MichaelBrunner on 01/07/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyTreeView.h" resolved

#include "mytreeview.h"

#include <iostream>

#include "ui_MyTreeView.h"
#include <QStandardItemModel>

struct Data
{
    std::string title;
    uint16_t index;
};

MyTreeView::MyTreeView(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::MyTreeView)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(this);
    m_model->setHorizontalHeaderLabels({"Column 1", "Column 2", "Column 3"});
    ui->treeView->setModel(m_model);
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setRootIsDecorated(false);
    ui->treeView->expandAll();

    std::vector<Data> dataContainer;
    for (uint16_t i = 0; i < 10; ++i) {
        dataContainer.push_back({"Item " + std::to_string(i), i});
    }

    for (const auto &itemData : dataContainer) {
        // QList<QStandardItem *> items;
        // items.append(new QStandardItem(QString::fromStdString(itemData.title)));
        // items.append(new QStandardItem(QString::number(itemData.index)));
        // items.append(new QStandardItem("Additional Data"));
        // m_model->appendRow(items);
        const auto item = new QStandardItem(QString::fromStdString(itemData.title));
        item->setData(itemData.index, Qt::DisplayRole);
        const auto child = new QStandardItem("Child");
        child->setData(itemData.index + 1, Qt::DisplayRole);
        item->appendRow(child);
        m_model->appendRow(item);
    }


    connect(ui->treeView, &QTreeView::clicked, this, &MyTreeView::onItemClicked);
}

MyTreeView::~MyTreeView()
{
    delete ui;
}
void MyTreeView::onItemClicked(const QModelIndex &index) const
{
    if (!index.isValid()) return;

    const auto item = m_model->itemFromIndex(index);
    if (!item) return;

    std::cout << "Item clicked:";
    std::cout << "  Text:" << item->text().toStdString();
    std::cout << "  Row:" << index.row();
    std::cout << "  Column:" << index.column();
    std::cout << "  Index:" << index.internalId();
    std::cout << "  Data:" << item->data(Qt::DisplayRole).toString().toStdString();
    std::cout << "  Has children:" << item->hasChildren();
}
