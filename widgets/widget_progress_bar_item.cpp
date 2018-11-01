#include "widget_progress_bar_item.h"

ItemProgressBar::ItemProgressBar(QWidget *parent)
    : QProgressBar{parent}
{
    setAlignment(Qt::AlignCenter);
    setFormat("%v / %m");
    setData(0, 0, 0);
}

void ItemProgressBar::setData(const int min, const int val, const int max)
{
    setMinimum(min);
    setMaximum(max);
    setValue(val);
}
