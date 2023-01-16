#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initWidget();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidget()
{
    isPressed = false;

    lineNum = 0;
    lineFlag1 = false;
    for(int i=0;i<5;i++)
    {
        linePoint[i] = QPoint(0,0);
    }

    lineFlag2 = false;
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);

    rectFlag = false;

    ui->lb_image->installEventFilter(this);
}

void Widget::upPaint()     //绘图
{    
    QPainter painter(ui->lb_image);
    //显示图片
    QString imagePath = "E:/PhotoTest/drawTest.PNG";   //图片对应路径
    painter.drawPixmap(0,0,400,300,QPixmap(imagePath));

    //显示图片的另一种方法：setPixmap,这里不要使用
    //QImage Image;
    //Image.load(imagePath);
    //ui->lb_image->setPixmap(QPixmap::fromImage(Image));

    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(1,1,100,50);
    painter.drawText(10,30,"测试文字");

    if(lineFlag1)   //line1
    {
        if(lineNum == 2)
        {
            painter.drawLine(linePoint[0],linePoint[1]);
        }
        else if(lineNum == 3)
        {
            painter.drawLine(linePoint[0],linePoint[1]);
            painter.drawLine(linePoint[1],linePoint[2]);
        }
        else if(lineNum == 4)
        {
            painter.drawLine(linePoint[0],linePoint[1]);
            painter.drawLine(linePoint[1],linePoint[2]);
            painter.drawLine(linePoint[2],linePoint[3]);
        }
        else if(lineNum == 5)
        {
            painter.drawLine(linePoint[0],linePoint[1]);
            painter.drawLine(linePoint[1],linePoint[2]);
            painter.drawLine(linePoint[2],linePoint[3]);
            painter.drawLine(linePoint[3],linePoint[4]);
        }
        else if(lineNum == 6)
        {
            painter.drawLine(linePoint[0],linePoint[1]);
            painter.drawLine(linePoint[1],linePoint[2]);
            painter.drawLine(linePoint[2],linePoint[3]);
            painter.drawLine(linePoint[3],linePoint[4]);
            painter.drawLine(linePoint[4],linePoint[0]);
        }
    }
    if(lineFlag2)   //line2
    {
        painter.drawLine(lineStartPoint,lineEndPoint);
    }
    if(rectFlag)   //line2
    {
        painter.drawRect(rect[0],rect[1],rect[2],rect[3]);
    }

    //p.drawLine(QLine(100,100,100,250));
    //painter.drawRect(100,100,200,150);
}

//鼠标按下
void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isPressed = true;
        if(lineFlag2)
        {
            lineStartPoint = QPoint(event->pos().x()-30,event->pos().y()-30);
            lineEndPoint = QPoint(event->pos().x()-30,event->pos().y()-30);
        }
        else if(rectFlag)
        {
            rect[0] = event->pos().x()-30;
            rect[1] = event->pos().y()-30;
        }
    }
}

//鼠标移动
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        if(lineFlag2)
        {
            lineEndPoint = QPoint(event->pos().x()-30,event->pos().y()-30);
        }
        else if(rectFlag)
        {
            rect[2] = event->pos().x()-30 - rect[0];
            rect[3] = event->pos().y()-30 - rect[1];
        }
        this->update();
    }
}

//鼠标抬起
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Release:"<<QPoint(event->pos().x()-30,event->pos().y()-30);
    if(event->button() == Qt::LeftButton)
    {
        if(lineFlag1)
        {
            //多个点(以5个点示例)
            if(lineNum == 0)
            {
                lineNum = 1;
                linePoint[0] = QPoint(event->pos().x()-30,event->pos().y()-30);
                this->update();
            }
            else if(lineNum == 1)
            {
                lineNum = 2;
                linePoint[1] = QPoint(event->pos().x()-30,event->pos().y()-30);
                this->update();
            }
            else if(lineNum == 2)
            {
                lineNum = 3;
                linePoint[2] = QPoint(event->pos().x()-30,event->pos().y()-30);
                this->update();
            }
            else if(lineNum == 3)
            {
                lineNum = 4;
                linePoint[3] = QPoint(event->pos().x()-30,event->pos().y()-30);
                this->update();
            }
            else if(lineNum == 4)
            {
                lineNum = 5;
                linePoint[4] = QPoint(event->pos().x()-30,event->pos().y()-30);
                this->update();
            }
            else if(lineNum == 5)
            {
                lineNum = 6;
                this->update();
            }
            else
            {
                lineNum = 0;
                this->update();
            }
        }
        else if(lineFlag2)
        {
            isPressed=false;
            lineEndPoint = QPoint(event->pos().x()-30,event->pos().y()-30);
            this->update();
        }
        else if(rectFlag)
        {
            isPressed=false;
            rect[2] = event->pos().x()-30 - rect[0];
            rect[3] = event->pos().y()-30 - rect[1];
            this->update();
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        isPressed=false;
        lineNum = 0;
        lineFlag1 = false;
        lineFlag2 = false;
        rectFlag = false;
        this->update();
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched ==ui->lb_image && event->type() == QEvent::Paint)
    {
        upPaint();
    }
    return QWidget::eventFilter(watched,event);
}

void Widget::on_pb_line_1_clicked()
{
    lineFlag1 = true;
    lineFlag2 = false;
    rectFlag = false;
    this->update();
}

void Widget::on_pb_line_2_clicked()
{
    lineFlag1 = false;
    lineFlag2 = true;
    rectFlag = false;
    this->update();
}

void Widget::on_pb_rect_clicked()
{
    lineFlag1 = false;
    lineFlag2 = false;
    rectFlag = true;
    this->update();
}

void Widget::on_pb_show_clicked()
{
    lineFlag1 = true;
    lineFlag2 = true;
    rectFlag = true;
    this->update();
}

void Widget::on_pb_clear_clicked()
{
    isPressed = false;

    lineNum = 0;
    lineFlag1 = false;
    for(int i=0;i<5;i++)
    {
        linePoint[i] = QPoint(0,0);
    }

    lineFlag2 = false;
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);

    rectFlag = false;
    for(int i=0;i<4;i++)
    {
        rect[i] = 0;
    }

    this->update();
}
