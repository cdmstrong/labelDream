#include "canvas2d.h"
#include <QMessageBox>
#include <QPainter>
#include <annotations/rectannoitem.h>

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

    //绘制标签






    //
//    qDebug() << "paintEvent" << curPoints.length();
    if(curPoints.length() >0) {
        p.drawRect(QRect(curPoints[0], curPoints[1]).normalized());
    }
    QBrush brush(Qt::SolidPattern);

    QList<AnnoItemPtr> list = annoM->getList();
    for(int i = 0;i <list.length(); i++) {
        auto ptr = Rectannoitem::cast_rectPtr(list[i]);
        QColor color = labelM->getLabel(ptr.get()->label)->color;
        brush.setColor(color);

        p.setBrush(brush);
        p.drawRect(QRect(ptr.get()->points[0], ptr.get()->points[1]).normalized());
        QFont font("Helvetica"); font.setFamily("Times"); font.setPixelSize(LABEL_PIXEL_SIZE);
        p.setFont(font);
        p.drawText(QPoint(ptr.get()->points[0].x() -20, ptr.get()->points[0].y()-20), ptr.get()->label);
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
                this->addAnno(curPoints);
                update();
                //存储画框
                curPoints.clear();
            }

            update();

        }
    }

}
void Canvas2d::addAnno(QList<QPoint> points) {
    //如果当前有选择的标签
    LabelProperty* text = labelM->getCurLabel();
    qDebug() << "cur" << text;
    if(!text) {
        QMessageBox::information(this, "error", "请选择您要标注的标签");
        return;
    }
    AnnoItemBase* anno = new Rectannoitem(text->id, text->label, points);

    annoM->addAnno(std::shared_ptr<AnnoItemBase>(anno));
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
