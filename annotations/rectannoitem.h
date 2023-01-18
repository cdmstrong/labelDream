#ifndef RECTANNOITEM_H
#define RECTANNOITEM_H
#include "annotationItemBase.h"
#include <memory>
using namespace std;
#include <QList>
class Rectannoitem: public AnnoItemBase {
public:
    Rectannoitem(QString id, QString label, QList<QPoint> points);
    static std::shared_ptr<Rectannoitem> cast_rectPtr(std::shared_ptr<AnnoItemBase> ptr);
    QList<QPoint> points;//两个点位 [[x1,y1],[x2, y2]]
private:


};

#endif // RECTANNOITEM_H
