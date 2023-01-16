#ifndef ANNOTATIONMANAGER_H
#define ANNOTATIONMANAGER_H

#include <QObject>

class AnnotationManager: public QObject {
    Q_OBJECT
public:
    AnnotationManager(QObject* parent = nullptr);
};

#endif // ANNOTATIONMANAGER_H
