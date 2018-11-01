#include "dialog_input_screen_rect.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QMouseEvent>

ScreenRectInputDialog::ScreenRectInputDialog(QWidget *parent)
    : QDialog{parent}
    , mw_rubberBand{new QRubberBand{QRubberBand::Rectangle, this}}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(QApplication::desktop()->screen()->rect().size());

    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Background, Qt::darkYellow);
    setAutoFillBackground(true);
    setPalette(newPalette);
    setWindowOpacity(0.5);
    setCursor(QCursor{Qt::CrossCursor});
}

const QRect &ScreenRectInputDialog::getSelectedRectangle() const {
    return m_selectedRectangle;
}

void ScreenRectInputDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mw_rubberBand->show();
    m_initPoint = event->pos();
}

void ScreenRectInputDialog::mouseMoveEvent(QMouseEvent *event) {
    mw_rubberBand->setGeometry(QRect(m_initPoint, event->pos()).normalized());
}

void ScreenRectInputDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }

    m_selectedRectangle = mw_rubberBand->geometry();
    accept();
}
