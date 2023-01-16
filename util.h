#ifndef UTIL_H
#define UTIL_H

#include <QList>
#include <QColor>
#include <QIcon>

namespace ColorUtils{

    extern QList<QColor> randomColors(int count);
    extern QColor randomColor();

    extern QIcon colorIcon(QColor color, QSize size = QSize(16,16));
    extern QString randId(int count = 5);
}
#endif // UTIL_H
