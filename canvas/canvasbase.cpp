#include "canvasbase.h"

CanvasBase::CanvasBase(LabelManager *labelM, AnnotationManager *annoM, QWidget *parent):
    labelM(labelM), annoM(annoM)
{

}





QString CanvasBase::modeString() const{
    return "";
}

void CanvasBase::setTaskMode(TaskMode mode)
{
    taskMode = mode;
}

