#include "annotationmanager.h"
#include "labelmanager.h"
#include <QDebug>
#include <QJsonArray>

AnnotationManager::AnnotationManager(QObject *parent): QObject (parent)
{
    name = "hhh";
}

void AnnotationManager::addAnno(AnnoItemPtr anno)
{
    this->annoList.push_back(anno);

    emit AnnotationAdded(anno);
}

void AnnotationManager::delAnno(int id)
{
    checkIdx(id);
    if(id == selectedIdx) selectedIdx = -1;
    qDebug() << annoList.length()<< id << "allLength";
    annoList.removeAt(id);
    emit AnnotationRemoved(id);
}

QList<AnnoItemPtr> AnnotationManager::getListByName(QString name)
{
    QList<AnnoItemPtr> filterList;

    for(int i = 0;i < annoList.length(); i++){
        AnnoItemPtr item = annoList.at(i);

    }
}

void AnnotationManager:: checkIdx(int id) {
    if(id < 0 || id > annoList.size() - 1) {
         throw "idx "+QString::number(id)+" out of range for anno container";
    }
}
void AnnotationManager::reNameLabel(QString name, QString reName) {
    for(int i = 0; i< annoList.length(); i++) {
        auto item = Rectannoitem::cast_rectPtr(annoList[i]);
        if(item.get()->label == name) {
            item.get()->label = reName;
        }
    }
}

void AnnotationManager::clearList()
{
    annoList.clear();
    emit cleared();
}


//保存
QJsonArray AnnotationManager::saveAnno()
{

    QJsonArray arr;
    for(int i = 0; i < annoList.length(); i++) {
        auto item = Rectannoitem::cast_rectPtr(annoList[i]);
        arr.push_back(item->toJsonObject());
    }

    return arr;

}
void AnnotationManager:: loadJson(QJsonArray arr) {
    annoList.clear();
    QList<AnnoItemPtr> items;
    for(int i = 0; i< arr.size(); i++ ) {
        QJsonValue value = arr.at(i);

        if(value.isObject()) {
            shared_ptr<AnnoItemBase> item = std::make_shared<Rectannoitem>();

            item->loadFromJson(value.toObject());
            items.push_back(std::static_pointer_cast<AnnoItemBase>(item));


//
        }
    };
    try {
        for (auto item: items){

            annoList.push_back(item);
//            annoList.insert(annoList.size(), item);
            emit AnnotationLoadAdded(item);
        }
    } catch (exception e ) {
        qDebug() << "bug" << e.what();
    }


}
AnnoItemPtr AnnotationManager::getItem(int id)
{
    return this->annoList.at(id);
}

void AnnotationManager::setSelectId(int id)
{
    selectedIdx = id;
    emit selectedChanged();
}
