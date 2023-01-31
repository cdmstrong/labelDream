#include <QListWidget>
#include <QString>
#include <QColor>
#include <QStringListModel>
#include "util.h"
#include "labelmanager.h"
#include "controllers/annotationmanager.h"
class CustomListWidget:public QListWidget {
   //自定义list
public:
    CustomListWidget(QWidget *parent=nullptr);

    void addCustomItemUncheckable(QString label, QColor color);
    void removeCustomItemByIdx(int idx);
    void update(QList<AnnoItemPtr> list);

public slots:
    void addCustomItem(LabelProperty label);
    bool changeItemColor(QString name, QColor color);
    bool changeItemName(QString name, QString reName);
    bool changeCheckState(QString name, Qt::CheckState check);

    void changeAnnoName(QList<AnnoItemPtr> list);


private:
    void mousePressEvent(QMouseEvent *event);
    QListWidgetItem *_findItemByName(QString labelName);
};
