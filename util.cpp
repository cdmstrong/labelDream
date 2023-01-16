#include "util.h";

#include <QColor>
#include <QIcon>
#include <QPixmap>
#include <QRandomGenerator>
QList<QColor> ColorUtils::randomColors(int seed) {

}

QColor ColorUtils::randomColor(){

        int r = 0;
        int g = 0;
        int b = 0;

        QString color = "";
        QString strR = "";
        QString strG = "";
        QString strB = "";



        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;

        bool ok = true;
        strR.setNum(r,16);
        if(strR.toInt(&ok,16)<16)
        {
            strR.prepend("0");
        }
        strG.setNum(g,16);
        if(strG.toInt(&ok,16)<16)
        {
            strG.prepend("0");
        }
        strB.setNum(b,16);
        if(strB.toInt(&ok,16)<16)
        {
            strB.prepend("0");
        }
        color.append("#"+strR+strG+strB);
        QColor a(r, g, b,150);
        return a;

}
QIcon ColorUtils::colorIcon(QColor color, QSize size) {
    QPixmap pix(size);
    if(color.isValid()) {
        pix.fill(color);
    } else {
        pix.fill(Qt::white);
    }
    return QIcon(pix);
}

QString ColorUtils::randId(int count) {
    QString str = "";
    for(int i = 0; i < count; i++) {
        str.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return str;

}

