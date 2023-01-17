#-------------------------------------------------
#
# Project created by QtCreator 2022-12-26T17:17:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labeldream
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    sort.cpp \
    Image.cpp \
    controllers/painter.cpp \
    util.cpp \
    widgets/customListWidget.cpp \
    controllers/labelmanager.cpp \
    canvas/canvas2d.cpp \
    canvas/canvasbase.cpp \
    controllers/annotationmanager.cpp \
    controllers/filemanager.cpp \
    annotations/annotationBase.cpp


HEADERS += \
        mainwindow.h \
    image.h \
    menu.h \
    controllers/painter.h \
    util.h \
    controllers/labelmanager.h \
    controllers/filemanager.h \
    controllers/annotationmanager.h \
    canvas/canvas2d.h \
    widgets/customListWidget.h \
    controllers/labelmanager.h \
    canvas/canvasbase.h \
    annotations/annotationBase.h \
    annotations/annotationBase.h

FORMS += \
        mainwindow.ui
INCLUDEPATH = controllers
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
