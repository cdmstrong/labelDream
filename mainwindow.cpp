#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QJsonArray>
#include <QJsonDocument>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    labelM(this),
    fileM(this),
    annoM(this),
    ui(new Ui::MainWindow)
{
//    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    ui->setupUi(this);

    //绑定按钮事件
//    ui->img->installEventFilter(this);
    //标签相关
    _setupLabelManager();
    _setupAnnoManager();
    //初始化画布 2d
    canvas2d = new Canvas2d(&labelM, &annoM, ui->scrollArea);

    canvas2d->setVisible(true);
    canvas2d->setEnabled(true);


    curCanvas = canvas2d;
    ui->scrollArea->setWidget(curCanvas);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    ui->scrollArea->setWidgetResizable(true);
    bindEvent();
    initToolBar();
    qDebug() << "current-widget" <<  ui->scrollArea->alignment();
}

//标签相关
void MainWindow::_setupLabelManager() {
    ui->labelsList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->labelsList, &QListWidget::customContextMenuRequested, this, &MainWindow::popLabelMenu);
    connect(&labelM, &LabelManager::labelAdded, ui->labelsList, &CustomListWidget::addCustomItem);
    connect(ui->labelsList, &QListWidget::currentItemChanged, &labelM, &LabelManager::changeActiveItem);
    connect(this, &MainWindow::clearLabel, this, [=](){
        labelM.clearCurLabel();
    });
    connect(&labelM, &LabelManager::allCleared, this, [=](){
        this->ui->labelsList->clear();
    });
}
void MainWindow:: bindEvent() {
    connect(ui->btnAdd, &QPushButton::clicked,this, &MainWindow::addLabel);

    //窗口大小变换

}
//添加标签
void MainWindow::addAnno() {

    if(labelM.getCurLabel() == nullptr) {
        QMessageBox::information(this, "error", "请选择您要标注的标签");
        return;
    }

}
//标签管理类
void MainWindow:: _setupAnnoManager() {
    connect(&annoM, &AnnotationManager::AnnotationAdded, this, [this](const AnnoItemPtr &item) {
       this->ui->annoList->addCustomItemUncheckable(Rectannoitem::cast_rectPtr(item).get()->toStr(), labelM.getCurLabel()->color);
    });
    connect(&annoM, &AnnotationManager::AnnotationLoadAdded, this, [this](const AnnoItemPtr &item) {
       this->ui->annoList->addCustomItemUncheckable(Rectannoitem::cast_rectPtr(item).get()->toStr(), labelM.getLabel(item->label)->color);
    });

    //点击标签进入编辑模式
    connect(ui->annoList, &QListWidget::itemSelectionChanged, this, [this]() {
       auto items = ui->annoList->selectedItems();

       if(items.length() == 0) {
           curCanvas->setCanvasMode(DRAW);
           annoM.setSelectId(-1);
           qDebug() << "选中的个数" << -1;
       } else {
           curCanvas -> setCanvasMode(SELECT);
           annoM.setSelectId(ui->annoList->row(items[0]));
           qDebug() << "选中的个数" << ui->annoList->row(items[0]);
       }
    });
    //点击删除菜单
    ui->annoList->setProperty("contextMenuPolicy", Qt:: CustomContextMenu);
    connect(ui->annoList, &QListWidget::customContextMenuRequested,
            this, &MainWindow::provideAnnoContextMenu);

    connect(&annoM, &AnnotationManager::AnnotationRemoved, this, &MainWindow::annoRemove);

    connect(&annoM, &AnnotationManager::annoChanged, this, &MainWindow::canvasUpdate);
    connect(&annoM, &AnnotationManager::selectedChanged, this, &MainWindow::canvasUpdate);
    connect(&annoM, &AnnotationManager::cleared, this, [=](){
        this->ui->annoList->clear();
    });
}
//右键弹出菜单
void MainWindow:: provideAnnoContextMenu(const QPoint& pos) {
    QModelIndex index = ui->annoList->indexAt(pos);

    if(!index.isValid()) return ;
    int row = index.row();

    QMenu menu;
    menu.addAction(tr("delete"));
    QAction* select = menu.exec(QCursor::pos());
    if(select) {
        if(select->text().contains("delete")) {
            annoM.delAnno(row);
            curCanvas->setCanvasMode(DRAW);
        }
    }
}
void MainWindow:: annoRemove(int idx) {
    ui->annoList->removeCustomItemByIdx(idx);
    if(annoM.getSelectId() == idx) {
        annoM.setSelectId(-1);
        curCanvas->setCanvasMode(DRAW);
    }
    canvasUpdate();
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
            bool suc = labelM.fixLabel(wellName, str);
            if(!suc) QMessageBox::information(this, "warnnig", "标签已存在");


        });
        connect(&labelM, &LabelManager::changeItemName, this, &MainWindow:: changeLabelName);
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
//修改标签名字事件
void MainWindow:: changeLabelName(QString name, QString reName) {
    qDebug() << "修改名字";
    ui->labelsList->changeItemName(name, reName);

    annoM.reNameLabel(name, reName);
    //修改所有的标签名字
    ui->annoList->changeAnnoName(annoM.getList());

}
void MainWindow::addLabel() {
    cout << "addLabel" << endl;
    QString name = ui->labelEdit->document()->toPlainText();
    bool suc = labelM.addLabel(name);
    if(!suc) QMessageBox::information(this, "err", "标签" + name + "已存在", QMessageBox::Ok);
}
void MainWindow::taskModeChanged(int idx) {
    qDebug() << idx;
    curCanvas->setTaskMode((TaskMode)idx);
}
void MainWindow::initToolBar() {

    QComboBox* task = new QComboBox(ui->toolBar);
    task->addItem("detection", DETECTION);
    task->addItem("segmentation", SEGMENTATION);
    task->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    ui->toolBar->insertWidget(ui->img_action, task);
    connect(task, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::taskModeChanged);
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
    connect(ui->save_action, &QAction::triggered, this, [=]() {saveFile();});
    connect(ui->pre_action, &QAction::triggered, this, [=]() {
        bool suc = fileM.pre();
        if(!suc) return;
        ui->filesList->setCurrentIndex(fileM.curRow);
        on_listView_clicked(fileM.curRow);
    });
    connect(ui->next_action, &QAction::triggered, this, [=]() {
        bool suc = fileM.next();
        if(!suc) return;
        ui->filesList->setCurrentIndex(fileM.curRow);
        on_listView_clicked(fileM.curRow);
    });
    connect(ui->init_action, &QAction::triggered, this, &MainWindow::adjustFitWindow);
    connect(ui->scanOut_action, &QAction::triggered, this, [=]() {curCanvas->setScale(curCanvas->getScale()*1.1);});
    connect(ui->scanIn_action, &QAction::triggered, this, [=]() {curCanvas->setScale(curCanvas->getScale()*0.9);});

    //监听鼠标移动
//    --------------------------------------状态栏相关--------------------------------------------------
    mousePosLabel = new QLabel("");
    ui->statusbar->addPermanentWidget(mousePosLabel);
    connect(canvas2d, &Canvas2d::mouseMove, this, &MainWindow::setMousePos);
}
void MainWindow::setMousePos(QPoint pos) {

    mousePosLabel->setText("(" + QString::number(pos.x()) + "," + QString::number(pos.y()) + ")" );
}
void MainWindow::saveFile() {
    //保存所有label and anno
    QJsonObject json;
    json.insert("annotations", annoM.saveAnno());
    json.insert("labels", labelM.saveLabel());

    fileM.saveJson(json);


}
QAction* MainWindow::addBar(string icon, string barName) {

    QIcon *file = new QIcon(icon.c_str());
    QAction *action = toolBar->addAction(*file, barName.c_str());
    return action;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::selectImg() {

    fileM.model->removeRows(0, fileM.model->rowCount());
    QString filename;
    filename = QFileDialog::getOpenFileName(nullptr,
                                             tr("select img"),
                                              "",
                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));

    QString img = filename.right(filename.length() - filename.lastIndexOf("/") - 1);
    fileM.imgName = img.split(".")[0];
    fileM.fullPath = filename.left(filename.lastIndexOf("/", -1));

    loadImg(filename);

}
void MainWindow::loadImg(QString filename){
    qDebug() << "open" << filename;
    if(!filename.isNull() && !filename.isEmpty()) {
        canvas2d->loadPixmap(filename);
        adjustFitWindow();
        clearImg();
        loadJson();
    }
}
void MainWindow::clearImg() {
     if(ui->annoList->count() < 0) return;
     ui->annoList->clear();
     annoM.clearList();

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
    QString str(fileM.fullPath);
    QString filename = str + "/" + fileM.model->data(index).toString();
    fileM.imgName = fileM.model->data(index).toString().split(".")[0];
    fileM.curRow = index;
    this->checkImg(filename);
    qDebug()<<"当前路径：" <<filename;
    loadImg(filename);
}

void  MainWindow::selectDir() {
    qDebug() << "打开路径";
    QString filename;
    filename=QFileDialog::getExistingDirectory(nullptr, tr("select dir"));
    if(!filename.isNull() && !filename.isEmpty()) {
        QDir dir(filename);
        QStringList images = dir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
        images.sort();
        QStringListIterator ite(images);
        //全路径
        QFileInfo fileDir;

        fileM.fullPath = filename.toStdString().data();
        fileM.model = new QStringListModel(this);
//        读取所有图片
        fileM.model->setStringList(images);
        fileM.curRow = fileM.model->index(0);
        ui->filesList->setModel(fileM.model);
        ui->filesList->setCurrentIndex(fileM.curRow);
        on_listView_clicked(fileM.curRow);
        connect(ui->filesList,&QListView::clicked,
                  this,&MainWindow::on_listView_clicked);
    }

}

void MainWindow::loadJson() {
    annoM.clearList();
    labelM.allClear();
    QJsonObject json = fileM.loadJson();
    if(!json.empty()) {
        qDebug() << "arr" << json.value("annotations").toArray();

        labelM.loadJson(json.value("labels").toArray());
        annoM.loadJson(json.value("annotations").toArray());
    }
//

 }
void MainWindow::canvasUpdate()
{

   canvas2d->update();

}

void MainWindow::on_labeltips_clicked() {

}

void MainWindow::on_labelsList_itemClicked(QListWidgetItem *item)
{

}
