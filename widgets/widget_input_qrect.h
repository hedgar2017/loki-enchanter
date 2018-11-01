#pragma once

#include <QWidget>
#include "interfaces/i_validable.h"

#include <QLabel>
#include <QPushButton>
#include <QRect>

#include "widget_line_edit_input_integer.h"

class QRectInputWidget : public QWidget, public IValidable
{
    Q_OBJECT

public:
    explicit QRectInputWidget(QWidget *parent = nullptr);
    QRectInputWidget(const QRectInputWidget &) = delete;
    void operator =(const QRectInputWidget &) = delete;
    virtual ~QRectInputWidget() = default;

    QRect                           get() const;
    void                            set(const QRect &);
    bool                            isValid(QString &error) const override;

private slots:
    void                            onSelect();

private:
    QLabel                          *mw_xCoordinateLabel;
    IntegerInputLineEdit            *mw_xCoordinateLineEdit;

    QLabel                          *mw_yCoordinateLabel;
    IntegerInputLineEdit            *mw_yCoordinateLineEdit;

    QLabel                          *mw_widthLabel;
    IntegerInputLineEdit            *mw_widthLineEdit;

    QLabel                          *mw_heightLabel;
    IntegerInputLineEdit            *mw_heightLineEdit;

    QPushButton                     *mw_selectPushButton;
};
