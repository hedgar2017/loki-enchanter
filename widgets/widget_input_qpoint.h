#pragma once

#include <QWidget>
#include "interfaces/i_validable.h"

#include <QLabel>
#include <QPushButton>
#include <QPoint>

#include "widget_line_edit_input_integer.h"

class QPointInputWidget : public QWidget, public IValidable
{
    Q_OBJECT

public:
    explicit QPointInputWidget(QWidget *parent = nullptr);
    QPointInputWidget(const QPointInputWidget &) = delete;
    void operator =(const QPointInputWidget &) = delete;
    virtual ~QPointInputWidget() = default;

    QPoint                          get() const;
    void                            set(const QPoint &);
    bool                            isValid(QString &error) const override;

private slots:
    void                            onSelect();

private:
    QLabel                          *mw_xCoordinateLabel;
    IntegerInputLineEdit            *mw_xCoordinateLineEdit;

    QLabel                          *mw_yCoordinateLabel;
    IntegerInputLineEdit            *mw_yCoordinateLineEdit;

    QPushButton                     *mw_selectPushButton;
};
