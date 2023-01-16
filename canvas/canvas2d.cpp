#include "canvas2d.h"
#include <QPainter>

Canvas2d::Canvas2d(LabelManager *labelM, AnnotationManager *annoM, QWidget *parent):CanvasBase(labelM, annoM, parent), pixmap()
{
    mousePos = QPoint(0, 0);
    setMouseTracking(true);
}

QSize Canvas2d::sizeUnscaled() const
{
    return pixmap.size();
}

void Canvas2d::paintEvent(QPaintEvent* event)
{

    if(pixmap.isNull()) {
        QWidget::paintEvent(event);
        return ;
    }
    QPainter p(this);
    qDebug() << scale;
    p.scale(scale, scale);
    p.setPen(QPen(Qt::black));
    p.drawLine(0, 50, 50, 300);
    p.drawPixmap(0, 0, pixmap);

    qDebug() << this->isVisible();


}

void Canvas2d::mouseMoveEvent(QMouseEvent *)
{
//    qDebug() << "mouse move";
}

void Canvas2d::mousePressEvent(QMouseEvent *)
{
    qDebug() << "mousePressEvent";
}

void Canvas2d::mouseReleaseEvent(QMouseEvent *)
{
    qDebug() << "mouseReleaseEvent";
}

void Canvas2d::loadPixmap(QPixmap img)
{
    //設置畫布图像
    pixmap = img;
    adjustSize();

    update();
}

void Canvas2d::setCanvasMode(CanvasMode)
{

}

void Canvas2d::setTaskMode(TaskMode)
{

}
void Canvas2d:: setDrawMode(DrawMode mode) {
    drawMode = mode;
}

void Canvas2d::setScale(qreal newScale)
{
    scale = newScale;
    adjustSize();
    update();
}
