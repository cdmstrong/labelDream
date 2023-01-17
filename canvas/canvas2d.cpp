#include "canvas2d.h"
#include <QPainter>

Canvas2d::Canvas2d(LabelManager *labelM, AnnotationManager *annoM, QWidget *parent):CanvasBase(labelM, annoM, parent), pixmap()
{
    mousePos = QPoint(0, 0);
    setMouseTracking(true);
    setTaskMode(DETECTION);
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

    p.scale(scale, scale);
    p.setPen(QPen(Qt::white));
    p.translate(offsetToCenter());
    p.drawPixmap(0, 0, pixmap);

    //
    qDebug() << "paintEvent" << curPoints.length();
    if(curPoints.length() >0) {
        p.drawRect(QRect(curPoints[0], curPoints[1]).normalized());
    }



}
QPoint Canvas2d::offsetToCenter()
{
    qreal s = scale;
    int w = int(pixmap.width() * s), h=int(pixmap.height() * s);
    int aw = this->size().width(), ah = this->size().height();
    int x = aw > w ? int((aw - w) / (2 * s)) : 0;
    int y = ah > h ? int((ah - h) / (2 * s)) : 0;
    return QPoint(x,y);
}

QPoint Canvas2d::pixelPos(QPoint pos)
{
    return pos/scale - offsetToCenter();
}

QPoint Canvas2d::boundedPixelPos(QPoint pos)
{
    pos = pos/scale - offsetToCenter();
    int x = pos.x(), y = pos.y();
    x = std::min(std::max(x, 0), pixmap.width());
    y = std::min(std::max(y, 0), pixmap.height());

    return QPoint(x, y);
}
void Canvas2d::mouseMoveEvent(QMouseEvent* event)
{
    if(pixmap.isNull()) return;

    emit mouseMove(boundedPixelPos(event->pos()));
    if(curPoints.length() == 2) {
        curPoints[1] = boundedPixelPos(event->pos());
    }
    update();
}

void Canvas2d::mousePressEvent(QMouseEvent* e)
{
    qDebug() << "mousePressEvent";
    QPoint mousePos = boundedPixelPos(e->pos());

    qDebug() << taskMode << e->button();
    //绘制矩形
    if(taskMode == DETECTION) {
        if(e->button() == Qt::LeftButton) {
            //选择点位绘制
            if(curPoints.length() == 0) {
                curPoints.push_back(mousePos);
                curPoints.push_back(mousePos);
            } else if(curPoints.length() == 2) {
                curPoints[1] = mousePos;
                update();
                //存储画框
                curPoints.clear();
            }

            update();

        }
    }

}

void Canvas2d::mouseReleaseEvent(QMouseEvent* e)
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

void Canvas2d::setTaskMode(TaskMode mode)
{
    taskMode = mode;
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
