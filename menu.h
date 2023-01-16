#ifndef MENU_H
#define MENU_H
#include <QToolBar>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QMainWindow>
//菜单操作类
namespace Ui {
class Menu;
}
class Menu {
public:
    Menu();
    Menu(QToolBar &q);
    void addBar(QToolBar &q);

};

#endif // MENU_H
