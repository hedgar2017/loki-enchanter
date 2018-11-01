#include "widget_input_qpoint.h"

#include <QGridLayout>

#include "widgets/widget_group_box_wrapper.h"
#include "dialogs/dialog_input_screen_point.h"

QPointInputWidget::QPointInputWidget(QWidget *parent)
    : QWidget{parent}

    , mw_xCoordinateLabel{new QLabel{this}}
    , mw_xCoordinateLineEdit{new IntegerInputLineEdit{this}}

    , mw_yCoordinateLabel{new QLabel{this}}
    , mw_yCoordinateLineEdit{new IntegerInputLineEdit{this}}

    , mw_selectPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(mw_xCoordinateLabel,          0, 0);
    layout->addWidget(mw_xCoordinateLineEdit,       0, 1);
    layout->addWidget(mw_yCoordinateLabel,          0, 2);
    layout->addWidget(mw_yCoordinateLineEdit,       0, 3);
    layout->addWidget(mw_selectPushButton,          0, 4);

    mw_xCoordinateLabel->setText(tr("X"));
    mw_yCoordinateLabel->setText(tr("Y"));
    mw_selectPushButton->setText(tr("PUSH_BUTTON_SELECT_TEXT"));

    layout->setMargin(0);
    setLayout(layout);

    connect(mw_selectPushButton, &QPushButton::clicked, this, &QPointInputWidget::onSelect);
}

QPoint QPointInputWidget::get() const
{
    return QPoint{
        mw_xCoordinateLineEdit->get(),
        mw_yCoordinateLineEdit->get()
        };
}

void QPointInputWidget::set(const QPoint &point)
{
    mw_xCoordinateLineEdit->set(point.x());
    mw_yCoordinateLineEdit->set(point.y());
}

bool QPointInputWidget::isValid(QString &error) const
{
    return     mw_xCoordinateLineEdit->isValid(error)
            && mw_yCoordinateLineEdit->isValid(error);
}

void QPointInputWidget::onSelect()
{
    ScreenPointInputDialog widget;
    if (widget.exec() == QDialog::Accepted) {
        set(widget.getSelectedPoint());
    };
}
