#pragma once

#include <QPixmap>
#include <QRect>

class Screenshot
{

public:
    static QPixmap make(const QRect &);
};
