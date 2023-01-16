#include "customListWidget.h"
#include <QDebug>
void CustomListWidget::addCustomItem(LabelProperty label) {
    QListWidgetItem * item1 = new QListWidgetItem(ColorUtils::colorIcon(label.color), label.label);
    item1->setFlags(item1->flags() | Qt::ItemIsUserCheckable);
    item1->setCheckState(label.visible?Qt::Checked:Qt::Unchecked);
    this->addItem(item1);

//    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //    connect(ui->labelsList, &QListWidget::customContextMenuRequested, this, &MainWindow::popMenu);
}

bool CustomListWidget::changeItemColor(QString name, QColor color)
{
    QListWidgetItem* item = _findItemByName(name);
    if(!item) return false;
    item->setIcon(ColorUtils::colorIcon(color));
    return true;
}

bool CustomListWidget::changeItemName(QString name, QString reName)
{
    QListWidgetItem* item = _findItemByName(name);
    if(!item) return false;
    qDebug() << "开始设置名字" << reName;
    item->setText(reName);
    return true;
}

bool CustomListWidget::changeCheckState(QString name, Qt::CheckState check)
{
    QListWidgetItem* item = _findItemByName(name);
    if(!item) return false;
    item->setCheckState(check);
    return true;

}
CustomListWidget::CustomListWidget(QWidget *parent):QListWidget(parent){
    setSelectionMode(QAbstractItemView::SingleSelection);
}

QListWidgetItem* CustomListWidget::_findItemByName(QString labelName) {
    auto items = this->findItems(labelName, Qt::MatchExactly);
    if(items.length() > 0) {
        return items[0];
    }
    return nullptr;
}

