#ifndef LABELMANAGER_H
#define LABELMANAGER_H

#include <QColor>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QMap>
#include <QListWidgetItem>
#include <QtDebug>
const int APACH = 100;
//先设置一个属性
class LabelProperty {

public:
    LabelProperty(QString label, QColor color, bool visible, QString id);
    LabelProperty();
    ~LabelProperty(){qDebug() << "我释放了";};
    QString label;
    QColor color;
    bool visible;
    QString id;
    QJsonObject toJsonObject(); //导出为json
    void loadFromJsonObject(QJsonObject json); //导入
};

class LabelManager:public QObject{
    Q_OBJECT
public:
    LabelManager(QObject* parent = nullptr);
    QMap<QString, LabelProperty>::iterator getLabel(QString name);
    bool addLabel(QString name);
    bool delLabel(QString name);
    bool fixLabel(QString name, QString reName);
    bool fixColor(QString name, QColor color);
    LabelProperty* getCurLabel() const; //获取当前选择的标签
    void clearCurLabel();
    QJsonArray saveLabel();
    void allClear();
    void loadJson(QJsonArray arr);
signals:
    void labelAdded(LabelProperty label);
    bool changeItemColor(QString name, QColor color);
    bool changeItemName(QString name, QString reName);
    bool changeCheckState(QString name, Qt::CheckState check);
    void allCleared();
public slots:
    void changeActiveItem(QListWidgetItem *current, QListWidgetItem *previous); //当前选择的标签
private:
    QMap<QString, LabelProperty> labels;

    LabelProperty* curLabel = nullptr; //当前的标签;
};

#endif // LABELMANAGER_H


