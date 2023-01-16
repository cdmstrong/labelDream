#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    labelM(this),
    fileM(this),
    annoM(this),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    initToolBar();
    //绑定按钮事件
//    ui->img->installEventFilter(this);
    //标签相关
    _setupLabelManager();
    //初始化画布 2d
    canvas2d = new Canvas2d(&labelM, &annoM, ui->scrollArea);

    canvas2d->setVisible(true);
    canvas2d->setEnabled(true);


    curCanvas = canvas2d;

    ui->scrollArea->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(curCanvas);

    bindEvent();

}

//标签相关
void MainWindow::_setupLabelManager() {
    ui->labelsList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelsList, &QListWidget::customContextMenuRequested, this, &MainWindow::popLabelMenu);
    connect(&labelM, &LabelManager::labelAdded, ui->labelsList, &CustomListWidget::addCustomItem);
}
void MainWindow:: bindEvent() {
    connect(ui->btnAdd, &QPushButton::clicked,this, &MainWindow::addLabel);

    //窗口大小变换

}
void MainWindow::addAnno() {

}

void MainWindow::popLabelMenu(const QPoint& pos)
{

    QListWidgetItem* curItem=ui->labelsList->currentItem();  //获取当前被点击的节点
    if(curItem==nullptr) return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    QString wellName = curItem->text();
    if(wellName != "wells")
    {
        QAction changeColor(QString::fromLocal8Bit("change color"),this);//重命名
        QAction deleteWell(QString ::fromLocal8Bit("delete"),this);//删除
        QAction reNameWell(QString ::fromLocal8Bit("change Name"),this);//
        //在界面上删除该item
        connect(&deleteWell, &QAction::triggered, this, [=]() {
            //delItem
            labelM.delLabel(wellName);
        });
        connect(&reNameWell,&QAction::triggered,this, [=]() {
            // rename
            bool ok;
            QString str = QInputDialog::getText(this, "修改标签", "修改的名称", QLineEdit::Normal, wellName, &ok);
            if(!ok || str.isEmpty()) return false;
            connect(&labelM, &LabelManager::changeItemName, ui->labelsList, &CustomListWidget::changeItemName);
            bool suc = labelM.fixLabel(wellName, str);
            if(!suc) QMessageBox::information(this, "warnnig", "标签已存在");
        });

        connect(&changeColor, &QAction::triggered, this, [=]() {
            // rename
            bool ok;
            QColor oriColor = labelM.getLabel(curItem->text()).value().color;
            QColor str = QColorDialog::getColor(oriColor, this, "choose color");
            if(!str.isValid()) return false;
            connect(&labelM, &LabelManager::changeItemColor, ui->labelsList, &CustomListWidget::changeItemColor);
            labelM.fixColor(wellName, str);
        });
        QMenu menu(ui->labelsList);

        menu.addAction(&reNameWell);
        menu.addAction(&changeColor);
        menu.addAction(&deleteWell);
        menu.exec(QCursor::pos());  //在当前鼠标位置显示

    }
}
void MainWindow::addLabel() {
    cout << "addLabel" << endl;
    QString name = ui->labelEdit->document()->toPlainText();
    bool suc = labelM.addLabel(name);
    if(!suc) QMessageBox::information(this, "err", "标签" + name + "已存在", QMessageBox::Ok);
}
void MainWindow::initToolBar() {

    QComboBox* task = new QComboBox(ui->toolBar);
    task->addItem("detection", DETECTION);
    task->addItem("segmentation", SEGMENTATION);
    task->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    ui->toolBar->insertWidget(ui->img_action, task);

    QComboBox* penShape = new QComboBox(ui->toolBar);
    penShape->addItem("rectangle", RECTANGLE);
    penShape->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    ui->toolBar->insertWidget(ui->img_action, penShape);

    QSpinBox* penSize = new QSpinBox(ui->toolBar);
    penSize->setRange(1, 10);
    penSize->setValue(1);

    ui->toolBar->insertWidget(ui->img_action, penSize);

    connect(ui->img_action, &QAction::triggered, this, [=]() {selectImg();});
    connect(ui->file_action, &QAction::triggered, this, [=]() {selectDir();});


}

QAction* MainWindow::addBar(string icon, string barName) {

    QIcon *file = new QIcon(icon.c_str());
    QAction *action = toolBar->addAction(*file, barName.c_str());
    return action;
}
//https://blog.csdn.net/XCJandLL/article/details/127458147
//bool MainWindow:: eventFilter(QObject *watched, QEvent *event) {
//    qDebug() << event->type() << endl;
//    if(watched ==ui->img  && event->type() == QEvent::Paint) {

//        upPaint();

//    }
//    return QWidget::eventFilter(watched, event);
//}
void MainWindow:: upPaint() {
    QPainter painter(ui->img);

    QString imagePath = "F:/python/yolov5/carData/images/01-90_265-231&522_405&574-405&571_235&574_231&523_403&522-0_0_3_1_28_29_30_30-134-56.jpg";
    QPixmap pix(imagePath);
    painter.drawPixmap((ui->img->width() - pix.width())/2, (ui->img->height() - pix.height())/2, pix.width(), pix.height(), QPixmap(imagePath));
//    ui->scrollArea->set
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
//    painter.drawRect(1, 1, 100, 500);
//    painter.drawText(10,30,"测试文字");
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgba64(171, 165, 141, 150));

    painter.setBrush(brush);
    painter.drawRect(rect[0],rect[1],rect[2],rect[3]);
}

//void MainWindow::mousePressEvent(QMouseEvent *event) {
//    if(event->button() == Qt::LeftButton) {
//        this->isPressed = true;
//        rect[0] = event->pos().x() - this->OFFSETX;
//        rect[1] = event->pos().y() - this->OFFSETY;
//        cout << rect[0] << "," << rect[1] << endl;
//    }
//}
////鼠标移动
//void MainWindow::mouseMoveEvent(QMouseEvent *event){
//    if(this->isPressed) {
//        rect[2] = event->pos().x()-this->OFFSETX - rect[0];
//        rect[3] = event->pos().y()-this->OFFSETY - rect[1];
//        qDebug() << "重绘" << endl;
//        this->update();

//    }
//}
//void MainWindow::mouseReleaseEvent(QMouseEvent *event){
//    if(event->button() == Qt:: LeftButton) {
//        isPressed=false;
//        rect[2] = event->pos().x()-this->OFFSETX - rect[0];
//        rect[3] = event->pos().y()-this->OFFSETY- rect[1];
//        this->update();
//        cout <<"release" << endl;
//    }
//}
MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::selectImg() {
    QString filename;


    filename=QFileDialog::getOpenFileName(nullptr,
                                             tr("select img"),
                                              "",
                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));

    if(!filename.isNull() && !filename.isEmpty()) {
        canvas2d->loadPixmap(filename);

        adjustFitWindow();


    }



}
qreal MainWindow::scaleFitWindow() const
{
    int w1 = ui->scrollArea->width() - 2; // -2 So that no scrollbars are generated.
    int h1 = ui->scrollArea->height() - 2;
    qreal a1 = static_cast<qreal>(w1)/h1;
    int w2 = curCanvas->sizeUnscaled().width();
    int h2 = curCanvas->sizeUnscaled().height();
    qreal a2 = static_cast<qreal>(w2)/h2;
    return a2>=a1 ? static_cast<qreal>(w1)/w2 : static_cast<qreal>(h1)/h2;
}

void MainWindow::adjustFitWindow()
{
    curCanvas->setScale(scaleFitWindow());
}

void MainWindow::checkImg(QString filename) {
    QImage* img=new QImage;
    img->load(filename);
    QImage npic = img->scaled(this->ui->img->width(),this->ui->img->height(),Qt::KeepAspectRatio);
//    this->ui->img->setPixmap(QPixmap::fromImage(npic));
}
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString str(this->fullPath);
    this->checkImg(str + "/" + this->model->data(index).toString());
    qDebug()<<this->model->data(index).toString();
    qDebug()<<"当前路径：" << this->fullPath;
}

void  MainWindow::selectDir() {
    QString filename;
    filename=QFileDialog::getExistingDirectory(nullptr, tr("select dir"));
    if(!filename.isNull() && !filename.isEmpty()) {
        QDir dir(filename);
        QStringList images = dir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
        images.sort();
        QStringListIterator ite(images);
        //全路径
        QFileInfo fileDir;
        cout << filename.toStdString().data() << endl;
        this->fullPath = filename.toStdString().data();
        this->model = new QStringListModel(this);
//        读取所有图片
        this->model->setStringList(images);

        ui->filesList->setModel(this->model);
        connect(ui->filesList,&QListView::clicked,
                  this,&MainWindow::on_listView_clicked);
    }

}



void MainWindow::on_labeltips_clicked()
{

}
