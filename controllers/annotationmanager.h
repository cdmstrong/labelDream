#ifndef ANNOTATIONMANAGER_H
#define ANNOTATIONMANAGER_H
#include <memory>
#include <QObject>
#include "annotations/annotationItemBase.h"
using AnnoItemPtr = std::shared_ptr<AnnoItemBase>; //共享指针别名

class AnnotationManager: public QObject {
    Q_OBJECT
public:
    AnnotationManager(QObject* parent = nullptr);
    void addAnno(AnnoItemPtr anno);
    void delAnno(QString id);
    QList<AnnoItemPtr> getList()  {return annoList; }
    AnnoItemPtr getItem(QString id) ;
    QString name;
private:
    QList<AnnoItemPtr> annoList;
};

#endif // ANNOTATIONMANAGER_H
