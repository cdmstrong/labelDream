#include <QListWidget>
#include <QString>
#include <QColor>
#include "util.h"
#include "labelmanager.h"
class CustomListWidget:public QListWidget {
   //自定义list
public:
    CustomListWidget(QWidget *parent=nullptr);

public slots:
    void addCustomItem(LabelProperty label);
    bool changeItemColor(QString name, QColor color);
    bool changeItemName(QString name, QString reName);
    bool changeCheckState(QString name, Qt::CheckState check);
private:

    QListWidgetItem *_findItemByName(QString labelName);
};
