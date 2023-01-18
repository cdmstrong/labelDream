#include <annotations/rectannoitem.h>


Rectannoitem::Rectannoitem(QString id, QString label, QList<QPoint> points):AnnoItemBase()
{
    this->points = points;
    this->id = id;
    this->label = label;
}

std::shared_ptr<Rectannoitem> Rectannoitem::cast_rectPtr(std::shared_ptr<AnnoItemBase> ptr)
{
    return std::static_pointer_cast<Rectannoitem>(ptr);
}

