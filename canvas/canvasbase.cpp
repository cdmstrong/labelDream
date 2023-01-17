#include "canvasbase.h"

CanvasBase::CanvasBase(const LabelManager *labelM, const AnnotationManager *annoM, QWidget *parent)
{

}

QString CanvasBase::modeString() const{
    return "";
}

void CanvasBase::setTaskMode(TaskMode mode)
{
    taskMode = mode;
}

