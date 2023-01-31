#ifndef RECTANNOITEM_H
#define RECTANNOITEM_H
#include "annotationItemBase.h"
#include <memory>
using namespace std;
#include <QList>
class Rectannoitem: public AnnoItemBase {
public:
    Rectannoitem(QRect rect, QString id, QString label, QList<QPoint> points);
    Rectannoitem();
    static std::shared_ptr<Rectannoitem> cast_rectPtr(std::shared_ptr<AnnoItemBase> ptr);
    QList<QPoint> points;//两个点位 [[x1,y1],[x2, y2]]
    QString toStr() const;
    QRect rect;
    QJsonObject toJsonObject() const override;
    void loadFromJson(const QJsonObject &json) override;
private:


};

#endif // RECTANNOITEM_H
