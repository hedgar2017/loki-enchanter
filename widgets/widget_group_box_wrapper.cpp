#include "widget_group_box_wrapper.h"

#include <QVBoxLayout>

GroupBoxWrapper::GroupBoxWrapper(QWidget *wrapped, QWidget *parent)
    : QGroupBox{parent}
{
    wrapped->setParent(this);
    setLayout(new QVBoxLayout{this});
    layout()->addWidget(wrapped);
}
