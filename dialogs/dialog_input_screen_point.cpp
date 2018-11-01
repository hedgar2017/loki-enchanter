#include "dialog_input_screen_point.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QMouseEvent>

ScreenPointInputDialog::ScreenPointInputDialog(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(QApplication::desktop()->screen()->rect().size());

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Background, Qt::darkGreen);
    setAutoFillBackground(true);
    setPalette(newPalette);
    setWindowOpacity(0.5);
    setCursor(QCursor{Qt::CrossCursor});
}

void ScreenPointInputDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }

    m_selectedPoint = event->pos();
    accept();
}

const QPoint &ScreenPointInputDialog::getSelectedPoint() const
{
    return m_selectedPoint;
}
