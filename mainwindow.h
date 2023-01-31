#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QToolBar>

#include <QString>
#include <QChar>
#include <QMainWindow>
#include <string>
#include <QFileDialog>
#include <QPoint>
#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QStringListModel>
#include <QMouseEvent>
#include "image.h"
#include "labelmanager.h"
#include "util.h"
#include <QListWidgetItem>
#include <QCheckBox>
#include "canvas/canvasbase.h"
#include <iostream>
#include <QStringListModel>
#include <QDebug>
#include <QListWidget>
#include <QBrush>
#include <QColorDialog>
#include <QTime>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QSpinBox>

#include <canvas/canvas2d.h>
using namespace std;


typedef void (*pcb)();
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initToolBar();
    QAction* addBar(string icon, string a);
   void on_listView_clicked(const QModelIndex &index);
   void selectImg();
   void checkImg(QString filename);
   void selectDir();
   QStringListModel *model;
   QString fullPath; //全路径
   QString imgName; //图片名字
   void upPaint();
   void bindEvent();
   QString randomColor();
   //管理类
   LabelManager labelM;
   FileManager fileM;
   AnnotationManager annoM;
   void popLabelMenu(const QPoint &pos);
   qreal scaleFitWindow() const;
   void adjustFitWindow();
   //鼠标位置 显示
   void setMousePos(QPoint pos);


   void taskModeChanged(int idx);
   void canvasUpdate();
   void _setupAnnoManager();
   void provideAnnoContextMenu(const QPoint &pos);
   void annoRemove(int idx);
   void changeLabelName(QString name, QString reName);
   void clearImg();
   void saveFile();
   void loadJson();
protected:
//   bool eventFilter(QObject *watched, QEvent *event);
//   void mousePressEvent(QMouseEvent *event);
//   void mouseMoveEvent(QMouseEvent *event);
//   void mouseReleaseEvent(QMouseEvent *event);

   QPainter painter;
private:
    Ui::MainWindow *ui;
    QToolBar *toolBar;
    //标签相关
    void _setupLabelManager();
    //状态栏 鼠标位置
    QLabel *mousePosLabel;

    bool isPressed;
    int rect[4] = {0};
    int OFFSETX = 10;
    int OFFSETY = 33;

    CanvasBase *curCanvas;
    Canvas2d *canvas2d;
signals:
    void clearLabel();
private slots:
    void addAnno();
    void addLabel();


    void on_labeltips_clicked();
    void on_labelsList_itemClicked(QListWidgetItem *item);
};


#endif // MAINWINDOW_H
