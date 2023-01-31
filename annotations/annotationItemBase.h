#ifndef ANNOTATIONBASE_H
#define ANNOTATIONBASE_H
#include <QString>
#include <QJsonObject>
class AnnoItemBase {
public:
    AnnoItemBase();
    //标签
    QString label;
    //坐标信息
    QString id;
    virtual QJsonObject toJsonObject() const;
    virtual void loadFromJson(const QJsonObject &json);
protected:

};

#endif
