#ifndef CANVAS2D_H
#define CANVAS2D_H

#include "canvasbase.h"
#include <QDebug>
#include <QMouseEvent>
class Canvas2d: public CanvasBase {
    Q_OBJECT
public:
    Canvas2d(LabelManager* labelM, AnnotationManager* annoM, QWidget* parent = nullptr);
    QSize sizeUnscaled() const override;



    // pixmap绘制位置的偏移量，这是由于当pixmap的大小小于画布（窗口）大小时，将pixmap绘制在中央
    QPoint offsetToCenter();
    // 将画布坐标转化为pixmap的像素坐标，具体为 pos / scale - offsetToCenter();
    QPoint pixelPos(QPoint pos);
    // 将画布坐标转化为pixmap的像素坐标，当超出pixmap的范围时，将其限制在pixmap边界上
    QPoint boundedPixelPos(QPoint pos);
    // 判断像素坐标pos是否超出pixmap的范围
    bool outOfPixmap(QPoint pos);
protected:
    void paintEvent(QPaintEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
private:
    QPixmap pixmap; //当前绘制的图像
    QPoint mousePos;    // 当前鼠标的像素坐标

    QList<QPoint> curPoints; //当前绘制的图形


signals:
    void mouseMove(QPoint pos);

public slots:
    void loadPixmap(QPixmap img);
    void setCanvasMode(CanvasMode) override;
    void setTaskMode(TaskMode) override;
    void setDrawMode(DrawMode) override;
    void setScale(qreal newScale) override;
};

#endif
