#ifndef ANNOTATIONMANAGER_H
#define ANNOTATIONMANAGER_H
#include <memory>
#include <QObject>
#include "annotations/annotationItemBase.h"
#include "annotations/rectannoitem.h"
using AnnoItemPtr = std::shared_ptr<AnnoItemBase>; //共享指针别名

class AnnotationManager: public QObject {
    Q_OBJECT
public:
    AnnotationManager(QObject* parent = nullptr);
    void addAnno(AnnoItemPtr anno);
    void delAnno(int id);
    QList<AnnoItemPtr> getList()  {return annoList; }
    QList<AnnoItemPtr> getListByName(QString name);
    AnnoItemPtr getItem(int id) ;
    QString name;
    void setSelectId(int id);
    int getSelectId() const{ return selectedIdx; };
    void checkIdx(int id);
    void reNameLabel(QString name, QString reName);
    void clearList();
    QJsonArray saveAnno();
    void loadJson(QJsonArray arr);
signals:
    void AnnotationAdded(AnnoItemPtr item);
    void AnnotationLoadAdded(AnnoItemPtr item);
    void AnnotationInserted(AnnoItemPtr item, int idx);
    void AnnotationModified(AnnoItemPtr item, int idx);
    void AnnotationRemoved(int idx);
    void AnnotationSwap(int idx);
    void cleared();
    void selectedChanged();
    void annoChanged();
private:
    QList<AnnoItemPtr> annoList;
    int selectedIdx;            // -1 表示未选中状态
};

#endif // ANNOTATIONMANAGER_H
