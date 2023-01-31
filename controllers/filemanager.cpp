
#include "filemanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
FileException::FileException(std::string message):message(message) {};
const char *FileException::what() const noexcept {
    return message.c_str();
}
FileManager::FileManager(QObject *parent) : QObject(parent) {

}

void FileManager:: saveJson(QJsonObject json) {
    QFile file(fullPath + "/"+ imgName + ".json");
    QJsonDocument jsonDoc;
    jsonDoc.setObject(json);
    qDebug() << "保存地址" << fullPath + imgName + ".json";
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(nullptr, "File Error", imgName+": file not open");
    }else{
        file.write(jsonDoc.toJson());
        file.close();
    }
}

bool FileManager:: checkSaveState() {

    QFile file(fullPath + "/" + imgName + ".json");
    if(file.exists()) {
        return true;
    }
    return false;
}

QJsonObject FileManager:: loadJson() {
    QFile file(fullPath + "/" + imgName + ".json");
    if(file.exists()) {


        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        if(doc.isObject()) {
            return doc.object();
        }
    } else {
        qDebug() << "json bu存在";
        return QJsonObject();
    }
}
void FileManager::allClear() {
    fileList.clear();
}
bool FileManager::pre() {
    if(curRow.row() <= 0) {
        QMessageBox::warning(nullptr, "Not more file", "没有上一张了");
        return false;
    }
    curRow = model->index(curRow.row() -1);
    return true;
}
bool FileManager:: next() {
    if(curRow.row() >= model->rowCount() -1) {
       QMessageBox::warning(nullptr, "Not more file", "没有下一张了");
       return false;
    }
    curRow = model->index(curRow.row() +1);
    return true;
}
