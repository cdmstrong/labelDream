#ifndef CANVASBASE_H
#define CANVASBASE_H

#include <QWidget>
#include <annotationmanager.h>
#include <filemanager.h>
#include <labelmanager.h>
// 用于表示当前任务的枚举类型：分别为2D检测，2D分割，3D检测，3D分割
enum TaskMode{
    DETECTION, SEGMENTATION
};
// 用于表示当前canvas的模式的枚举类型：分别表示绘制模式，选中模式，移动模式
// DRAW 用于绘制一个标注
// SELECT 用于选中一个标注并编辑之
// MOVE 仅限3D任务，用于移动焦点的位置，对应移动三个切面的坐标
enum CanvasMode{
    DRAW, SELECT, MOVE
};
enum DrawMode{
    RECTANGLE,
    CONTOUR, SQUAREPEN, CIRCLEPEN, POLYGEN
};
class CanvasBase: public QWidget {
    Q_OBJECT
public:
    explicit CanvasBase(LabelManager* labelM, AnnotationManager* annoM, QWidget* parent = nullptr);
    TaskMode getTaskMode() const {return taskMode;} //结尾加上 const 表示常成员函数，这种函数只能读取成员变量的值，而不能修改成员变量的值
    CanvasMode getCanvasMode() const {return canvasMode;}
    DrawMode getDrawMode() const {return drawMode;}
    qreal getScale() const { return scale; }
    int getLastPenWidth() const { return lastPenWidth; }

    // 返回未缩放情况下的画布大小，可用于适应窗口大小（fitWindow）等
    virtual QSize sizeUnscaled() const = 0;
    // 返回一个字符串描述当前的模式信息（包括task，mode，drawMode），可用于状态栏等
    virtual QString modeString() const;
protected:

    qreal scale; //当前的缩放比例
    TaskMode taskMode; //当前模式
    CanvasMode canvasMode; //画布模式
    DrawMode drawMode; //画笔模式

    LabelManager* labelM;
    AnnotationManager* annoM;

    int lastPenWidth; //最后画笔大小
    int curPenWidth; //当前画笔大小
public slots:
    virtual void setScale(qreal newScale) = 0;
    virtual void setTaskMode(TaskMode) = 0;
    virtual void setCanvasMode(CanvasMode) = 0;
    virtual void setDrawMode(DrawMode) = 0;
};

#endif // CANVASBASE_H
