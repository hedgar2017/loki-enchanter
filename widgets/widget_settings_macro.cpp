#include "widget_settings_macro.h"

#include <QGridLayout>
#include <QMessageBox>

#include <stdexcept>

#include "dialogs/dialog_input_screen_point.h"
#include "widgets/widget_group_box_wrapper.h"

MacroSettingsWidget::MacroSettingsWidget(MacroModel &model, QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_scrollPointInput{new QPointInputWidget{this}}
    , mw_itemPointInput{new QPointInputWidget{this}}
    , mw_confirmPointInput{new QPointInputWidget{this}}
    , mw_scrollPointDelayInput{new IntegerInputLineEdit{this}}
    , mw_itemPointDelayInput{new IntegerInputLineEdit{this}}

    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_scrollPointInput),       0, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemPointInput),         1, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_confirmPointInput),      2, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_scrollPointDelayInput),  3, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemPointDelayInput),    3, 1);
    layout->addWidget(mw_resetPushButton,                               4, 0, 1, 2);

    GET_GROUP_BOX_WRAPPER(mw_scrollPointInput)->setTitle(tr("INPUT_SCROLL_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_itemPointInput)->setTitle(tr("INPUT_ITEM_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_confirmPointInput)->setTitle(tr("INPUT_CONFIRM_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_scrollPointDelayInput)->setTitle(tr("INPUT_SCROLL_POINT_DELAY_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_itemPointDelayInput)->setTitle(tr("INPUT_ITEM_POINT_DELAY_TITLE"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    setLayout(layout);
    setFixedHeight(300);
    reset();

    connect(mw_resetPushButton, &QPushButton::clicked, this, &MacroSettingsWidget::reset);
}

void MacroSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    mr_model.setScrollPoint(mw_scrollPointInput->get());
    mr_model.setItemPoint(mw_itemPointInput->get());
    mr_model.setConfirmPoint(mw_confirmPointInput->get());
    mr_model.setScrollPointDelay(mw_scrollPointDelayInput->get());
    mr_model.setItemPointDelay(mw_itemPointDelayInput->get());
}

bool MacroSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    if (!mw_scrollPointInput->isValid(error)) {
        errorList << tr("ERROR_SCROLL_POINT_INVALID");
        isValid = false;
    }
    if (!mw_itemPointInput->isValid(error)) {
        errorList << tr("ERROR_ITEM_POINT_INVALID");
        isValid = false;
    }
    if (!mw_confirmPointInput->isValid(error)) {
        errorList << tr("ERROR_CONFIRM_POINT_INVALID");
        isValid = false;
    }
    if (!mw_scrollPointDelayInput->isValid(error)) {
        errorList << tr("ERROR_SCROLL_POINT_DELAY_INVALID");
        isValid = false;
    }
    if (!mw_itemPointDelayInput->isValid(error)) {
        errorList << tr("ERROR_ITEM_POINT_DELAY_INVALID");
        isValid = false;
    }
    error += errorList.join("\r\n");
    return isValid;
}

void MacroSettingsWidget::reset()
{
    mw_scrollPointInput->set(mr_model.getScrollPoint());
    mw_itemPointInput->set(mr_model.getItemPoint());
    mw_confirmPointInput->set(mr_model.getConfirmPoint());
    mw_scrollPointDelayInput->set(mr_model.getScrollPointDelay());
    mw_itemPointDelayInput->set(mr_model.getItemPointDelay());
}
