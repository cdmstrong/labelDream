#include "annotationItemBase.h"
AnnoItemBase::AnnoItemBase()
{

}

QJsonObject AnnoItemBase::toJsonObject() const
{
    QJsonObject object;
    object.insert("label", label);
    return object;
}

void AnnoItemBase::loadFromJson(const QJsonObject &json)
{
    if (json.contains("label")){
        QJsonValue value = json.value("label");
        if (value.isString()){
            label = value.toString();
        }else {
            throw "value of <label> is illegal";
        }
    }else{
        throw "no data <label>";
    }
}
