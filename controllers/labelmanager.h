#ifndef LABELMANAGER_H
#define LABELMANAGER_H

#include <QColor>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QMap>
const int APACH = 100;
//先设置一个属性
class LabelProperty {

public:
    LabelProperty(QString label, QColor color, bool visible, QString id);
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
signals:
    void labelAdded(LabelProperty label);
    bool changeItemColor(QString name, QColor color);
    bool changeItemName(QString name, QString reName);
    bool changeCheckState(QString name, Qt::CheckState check);
private:
    QMap<QString, LabelProperty> labels;
};

#endif // LABELMANAGER_H


