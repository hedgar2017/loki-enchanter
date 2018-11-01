#include "screenshot.h"

#include <QGuiApplication>
#include <QScreen>

QPixmap Screenshot::make(const QRect &rect)
{
    return QGuiApplication::primaryScreen()->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());
}
