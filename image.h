#ifndef IMAGE_H
#define IMAGE_H
//图像单张类， 管理单张图片
#include <QLabel>
#include <iostream>

using namespace std;

struct annonationType {
    QColor annoColor;
    QString annoName;
    int id;
    int rect[4];
};
struct labelType {
    QColor labelColor;
    QString labelName;

};

class Image2d: QObject{
    Q_OBJECT
public:
    Image2d();

    ~Image2d();

    void addAnno();
    void addLabel(labelType &label);
    QString randomColor();

protected:
    QString fullPath; //当前的选择路径
    QList<annonationType> annoList;//当前图片所有的标注位置信息
    QList<labelType> labelList; //存放标签信息
    int curLabel; //当前选中的标签数字

};

#endif // IMAGE_H
