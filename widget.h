#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initWidget();
    void upPaint();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pb_line_1_clicked();
    void on_pb_line_2_clicked();
    void on_pb_rect_clicked();
    void on_pb_show_clicked();
    void on_pb_clear_clicked();

private:
    Ui::Widget *ui;

    bool isPressed;

    //line1
    int lineNum;
    bool lineFlag1;
    QPoint linePoint[5];

    //line2
    bool lineFlag2;
    QPoint lineStartPoint;
    QPoint lineEndPoint;

    //rect
    bool rectFlag;
    int rect[4] = {0};

};
#endif // WIDGET_H
