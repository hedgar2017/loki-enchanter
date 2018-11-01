#pragma once

#include <QDialog>
#include <QRect>
#include <QPoint>
#include <QRubberBand>

class ScreenRectInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreenRectInputDialog(QWidget *parent = nullptr);
    ScreenRectInputDialog(const ScreenRectInputDialog &) = delete;
    void operator =(const ScreenRectInputDialog &) = delete;
    virtual ~ScreenRectInputDialog() override = default;

    const QRect&        getSelectedRectangle() const;

protected:
    void                mousePressEvent(QMouseEvent *) override;
    void                mouseMoveEvent(QMouseEvent *) override;
    void                mouseReleaseEvent(QMouseEvent *) override;

private:
    QRubberBand         *mw_rubberBand;
    QPoint              m_initPoint;
    QRect               m_selectedRectangle;
};
