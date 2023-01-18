#include "annotationmanager.h"

AnnotationManager::AnnotationManager(QObject *parent): QObject (parent)
{
    name = "hhh";
}

void AnnotationManager::addAnno(AnnoItemPtr anno)
{
    this->annoList.push_back(anno);
}

AnnoItemPtr AnnotationManager::getItem(QString id)
{
    return this->annoList.at(1);
}
