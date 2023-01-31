#include "labelmanager.h"
#include <QDebug>

#include <QJsonArray>
#include <QMessageBox>
#include "filemanager.h"
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
    //如果有存在的标签， 返回删除失败

    return true;
}

bool LabelManager::fixLabel(QString name, QString reName)
{
    if(labels.find(reName) != labels.end()) return false;

    labels.find(name)->label = reName;
    LabelProperty label = labels.find(name).value();
    labels.insert(reName, label);
//    labels.remove(name);
    //是否是当前的标签
    if(curLabel->label == name) {
        curLabel = &labels.find(reName).value();
    }
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

void LabelManager::changeActiveItem(QListWidgetItem *current, QListWidgetItem *)
{
    if(labels.isEmpty()) return;
    curLabel = &labels.find(current->text()).value();
    qDebug() << "curIdx" << curLabel->label;
}

LabelProperty* LabelManager::getCurLabel() const
{
    return curLabel;

}

void LabelManager::clearCurLabel() {
    curLabel = nullptr;
}

QJsonArray LabelManager::saveLabel()
{

    QJsonArray arr;
    for(auto it = labels.begin(); it!= labels.end(); it++) {
        arr.push_back(it.value().toJsonObject());
    }

    return arr;
}
void LabelManager::allClear() {
    if(labels.isEmpty()) return;
    curLabel = nullptr;
    labels.clear();
    emit allCleared();
}
void LabelManager::loadJson(QJsonArray arr) {
    labels.clear();
    for(int i = 0; i< arr.size(); i++ ) {
        QJsonValue value = arr.at(i);
        if(value.isObject()) {
            LabelProperty item;
            item.loadFromJsonObject(value.toObject());
            labels.insert(item.label, item);

            emit labelAdded(item);
        }
    };
}
//--------------------------------------LabelProperty ----------------------------------------

LabelProperty::LabelProperty(QString label, QColor color, bool visible, QString id): label(label),color(color), visible(visible), id(id){
    color.setAlpha(APACH);
    this->color = color;
}
LabelProperty::LabelProperty():label(), color(), visible(true), id(-1) {
}
QJsonObject LabelProperty::toJsonObject() {
    QJsonObject json;
    QJsonArray colorArr;
    colorArr.push_back(color.red());
    colorArr.push_back(color.green());
    colorArr.push_back(color.blue());
    json.insert("rgb", colorArr);
    json.insert("visible", visible);
    json.insert("label", label);
    return json;
}; //导出为json

void LabelProperty::loadFromJsonObject(QJsonObject json)
{

    if (json.contains("label")){
        QJsonValue value = json.value("label");
        if (value.isString()){
            label = value.toString();
        }else{
            throw FileException("value of <label> is illegal");
        }
    }else{
        throw FileException("no data <label>");
    }

    if (json.contains("rgb")){
        QJsonValue value = json.value("rgb");
        if (value.isArray()){
            QJsonArray array = value.toArray();
//            if (!array.at(0).isDouble() || !array.at(1).isDouble() || !array.at(2).isDouble()){
//                throw FileException("value of <color> is illegal");
//            }
            int r=static_cast<int>(array.at(0).toDouble());
            int g=static_cast<int>(array.at(1).toDouble());
            int b=static_cast<int>(array.at(2).toDouble());
            color = QColor(r,g,b);
        }else{
            throw FileException("value of <color> is illegal");
        }
    }else{
        throw "no data <color>";
    }

    if (json.contains("visible")){
        QJsonValue value = json.value("visible");
        if (value.isBool()){
            visible = value.toBool();
        }else{
            throw FileException("value of <visible> is illegal");
        }
    }else{
        throw FileException("no data <visible>");
    }


}

