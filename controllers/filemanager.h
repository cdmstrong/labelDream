#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QStringListModel>
#include <exception>
class FileException:public std::exception{
public:
    FileException(std::string message);
    // 返回 message
    const char * what() const noexcept;
private:
    std::string message;
};

class FileManager: public QObject {
    Q_OBJECT
public:
    FileManager(QObject* parent = nullptr);
    QString fullPath; //当前选择的路径
    QString imgName; // 当前文件名字
    QStringListModel *model;
    QModelIndex curRow;
    QString fileList; //所有文件的列表
    void saveJson(QJsonObject json);
    bool checkSaveState();
    QJsonObject loadJson();
    void allClear();
    bool pre();
    bool next();
};

#endif // FILEMANAGER_H
