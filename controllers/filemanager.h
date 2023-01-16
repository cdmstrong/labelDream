#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class FileManager: public QObject {
    Q_OBJECT
public:
    FileManager(QObject* parent = nullptr);
};

#endif // FILEMANAGER_H
