#include <annotations/rectannoitem.h>
#include <QDebug>
#include <QJsonArray>
#include <filemanager.h>

Rectannoitem::Rectannoitem(QRect rect, QString id, QString label, QList<QPoint> points): AnnoItemBase(), rect(rect)
{
    this->points = points;
    this->id = id;
    qDebug() << "标签" << label;
    this->label = label;
}

Rectannoitem::Rectannoitem()
{

}

std::shared_ptr<Rectannoitem> Rectannoitem::cast_rectPtr(std::shared_ptr<AnnoItemBase> ptr)
{
    return std::static_pointer_cast<Rectannoitem>(ptr);
}

QString Rectannoitem::toStr() const
{
    QString topLeft = "(" + QString::number(rect.topLeft().x()) + "," +QString::number(rect.topLeft().y()) + ")";
    QString bottomRight = "(" + QString::number(rect.bottomRight().x()) + "," +QString::number(rect.bottomRight().y()) + ")";
    return label+" " + " ("+topLeft+","+bottomRight+")";
}

QJsonObject Rectannoitem::toJsonObject() const
{
    QJsonObject object = AnnoItemBase::toJsonObject();
    QJsonArray point1, point2, points;
    point1.push_back(rect.topLeft().x());
    point1.push_back(rect.topLeft().y());
    point2.push_back(rect.bottomRight().x());
    point2.push_back(rect.bottomRight().y());
    points.push_back(point1);
    points.push_back(point2);

    object.insert("points", points);
    return object;
}

void Rectannoitem::loadFromJson(const QJsonObject &json)
{
    qDebug() <<"Rect 的json是" << json;
    AnnoItemBase::loadFromJson(json);
    if (json.contains("points")){
        QJsonValue value = json.value("points");
        if (value.isArray()){
            QJsonArray array = value.toArray();
            QJsonValue point1 = array.at(0);
            if (point1.isArray()){
                QJsonArray point1Array = point1.toArray();

                int x=static_cast<int>(point1Array.at(0).toDouble());
                int y=static_cast<int>(point1Array.at(1).toDouble());
                rect.setTopLeft(QPoint(x,y));
                points.push_back(QPoint(x,y));
            }else{
                throw FileException("value of points[0] is illegal");
            }
            QJsonValue point2 = array.at(1);
            if (point2.isArray()){
                QJsonArray point2Array = point2.toArray();

                int x=static_cast<int>(point2Array.at(0).toDouble());
                int y=static_cast<int>(point2Array.at(1).toDouble());
                rect.setBottomRight(QPoint(x,y));
                points.push_back(QPoint(x,y));
            }else{
                throw FileException("value of points[1] is illegal");
            }
        }else{
            throw FileException("value of <points> is illegal");
        }
    }else{
        throw FileException("no data <points>");
    }
}


