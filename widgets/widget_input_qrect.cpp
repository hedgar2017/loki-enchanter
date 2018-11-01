#include "widget_input_qrect.h"

#include <QGridLayout>

#include "widgets/widget_group_box_wrapper.h"
#include "dialogs/dialog_input_screen_rect.h"

QRectInputWidget::QRectInputWidget(QWidget *parent)
    : QWidget{parent}

    , mw_xCoordinateLabel{new QLabel{this}}
    , mw_xCoordinateLineEdit{new IntegerInputLineEdit{this}}

    , mw_yCoordinateLabel{new QLabel{this}}
    , mw_yCoordinateLineEdit{new IntegerInputLineEdit{this}}

    , mw_widthLabel{new QLabel{this}}
    , mw_widthLineEdit{new IntegerInputLineEdit{this}}

    , mw_heightLabel{new QLabel{this}}
    , mw_heightLineEdit{new IntegerInputLineEdit{this}}

    , mw_selectPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(mw_xCoordinateLabel,          0, 0);
    layout->addWidget(mw_xCoordinateLineEdit,       0, 1);
    layout->addWidget(mw_widthLabel,                0, 2);
    layout->addWidget(mw_widthLineEdit,             0, 3);
    layout->addWidget(mw_yCoordinateLabel,          1, 0);
    layout->addWidget(mw_yCoordinateLineEdit,       1, 1);
    layout->addWidget(mw_heightLabel,               1, 2);
    layout->addWidget(mw_heightLineEdit,            1, 3);
    layout->addWidget(mw_selectPushButton,          0, 4, 2, 1);

    mw_selectPushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    mw_xCoordinateLabel->setText(tr("X"));
    mw_yCoordinateLabel->setText(tr("Y"));
    mw_widthLabel->setText(tr("WIDTH"));
    mw_heightLabel->setText(tr("HEIGHT"));
    mw_selectPushButton->setText(tr("PUSH_BUTTON_SELECT_TEXT"));

    layout->setMargin(0);
    setLayout(layout);

    connect(mw_selectPushButton, &QPushButton::clicked, this, &QRectInputWidget::onSelect);
}

QRect QRectInputWidget::get() const
{
    return QRect{
        mw_xCoordinateLineEdit->get(),
        mw_yCoordinateLineEdit->get(),
        mw_widthLineEdit->get(),
        mw_heightLineEdit->get()
        };
}

void QRectInputWidget::set(const QRect &rect)
{
    mw_xCoordinateLineEdit->set(rect.x());
    mw_yCoordinateLineEdit->set(rect.y());
    mw_widthLineEdit->set(rect.width());
    mw_heightLineEdit->set(rect.height());
}

bool QRectInputWidget::isValid(QString &error) const
{
    return    mw_xCoordinateLineEdit->isValid(error)
           && mw_yCoordinateLineEdit->isValid(error)
           && mw_widthLineEdit->isValid(error)
           && mw_heightLineEdit->isValid(error);
}

void QRectInputWidget::onSelect()
{
    ScreenRectInputDialog widget;
    if (widget.exec() == QDialog::Accepted) {
        set(widget.getSelectedRectangle());
    };
}
