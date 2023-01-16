#ifndef CANVAS2D_H
#define CANVAS2D_H

#include "canvasbase.h"
#include <QDebug>
class Canvas2d: public CanvasBase {
    Q_OBJECT
public:
    Canvas2d(LabelManager* labelM, AnnotationManager* annoM, QWidget* parent = nullptr);
    QSize sizeUnscaled() const override;


protected:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent* ) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
private:
    QPixmap pixmap; //当前绘制的图像
    QPoint mousePos;    // 当前鼠标的像素坐标

public slots:
    void loadPixmap(QPixmap img);
    void setCanvasMode(CanvasMode) override;
    void setTaskMode(TaskMode) override;
    void setDrawMode(DrawMode) override;
    void setScale(qreal newScale) override;
};

#endif
