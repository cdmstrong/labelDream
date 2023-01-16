#include "labelmanager.h"
#include <QDebug>

#include <QMessageBox>
#include "util.h"
//获取label

LabelManager::LabelManager(QObject *parent):QObject (parent)
{

}

QMap<QString, LabelProperty>::iterator LabelManager::getLabel(QString name)
{
    return labels.find(name);
}

bool LabelManager::addLabel(QString name)
{

    if(getLabel(name) != labels.end()) return false;

    LabelProperty label(name, ColorUtils::randomColor(), true, ColorUtils::randId());

    labels.insert(name, label);
    emit labelAdded(label);
    return true;
}

bool LabelManager::delLabel(QString name)
{
    return true;
}

bool LabelManager::fixLabel(QString name, QString reName)
{
    if(labels.find(reName) != labels.end()) return false;
    labels.find(name).value().label = reName;
    qDebug() << "原来的名字" << labels.find(name).value().label<< "修改的名字" << reName;

    emit changeItemName(name, reName);
    return true;
}

bool LabelManager::fixColor(QString name, QColor color)
{
    color.setAlpha(APACH);
    getLabel(name).value().color = color;
    emit changeItemColor(name, color);
    return true;
}

//--------------------------------------LabelProperty ----------------------------------------

LabelProperty::LabelProperty(QString label, QColor color, bool visible, QString id): label(label),color(color), visible(visible), id(id){
    color.setAlpha(APACH);
    this->color = color;
}

