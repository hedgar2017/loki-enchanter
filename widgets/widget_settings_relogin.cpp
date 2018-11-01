#include "widget_settings_relogin.h"

#include <QGridLayout>
#include <QMessageBox>

#include <stdexcept>

#include "dialogs/dialog_input_screen_point.h"
#include "widgets/widget_group_box_wrapper.h"

ReloginSettingsWidget::ReloginSettingsWidget(ReloginModel &model, QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_isEnabledCheckBox{new QCheckBox{this}}
    , mw_reloginPeriodInput{new IntegerInputLineEdit{this}}
    , mw_cancelPointInput{new QPointInputWidget{this}}
    , mw_menuPointInput{new QPointInputWidget{this}}
    , mw_restartPointInput{new QPointInputWidget{this}}
    , mw_confirmPointInput{new QPointInputWidget{this}}
    , mw_loggingOutDelayInput{new IntegerInputLineEdit{this}}
    , mw_startPointInput{new QPointInputWidget{this}}
    , mw_loggingInDelayInput{new IntegerInputLineEdit{this}}
    , mw_sitPointInput{new QPointInputWidget{this}}
    , mw_isMiddleClickEnabledCheckBox{new QCheckBox{this}}
    , mw_isMiddleClickDoubleCheckBox{new QCheckBox{this}}

    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(mw_isEnabledCheckBox,                                 0, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_reloginPeriodInput),         1, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_cancelPointInput),           2, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_menuPointInput),             3, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_restartPointInput),          4, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_confirmPointInput),          5, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_startPointInput),            6, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_sitPointInput),              7, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_loggingOutDelayInput),       8, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_loggingInDelayInput),        8, 1);
    layout->addWidget(mw_isMiddleClickEnabledCheckBox,                      9, 0);
    layout->addWidget(mw_isMiddleClickDoubleCheckBox,                       9, 1);
    layout->addWidget(mw_resetPushButton,                                   10, 0, 1, 2);

    mw_isEnabledCheckBox->setText(tr("CHECK_BOX_IS_ENABLED_TEXT"));
    GET_GROUP_BOX_WRAPPER(mw_reloginPeriodInput)->setTitle(tr("INPUT_RELOGIN_PERIOD_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_cancelPointInput)->setTitle(tr("INPUT_CANCEL_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_menuPointInput)->setTitle(tr("INPUT_MENU_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_restartPointInput)->setTitle(tr("INPUT_RESTART_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_confirmPointInput)->setTitle(tr("INPUT_CONFIRM_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_startPointInput)->setTitle(tr("INPUT_START_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_sitPointInput)->setTitle(tr("INPUT_SIT_POINT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_loggingOutDelayInput)->setTitle(tr("INPUT_LOGGING_OUT_DELAY_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_loggingInDelayInput)->setTitle(tr("INPUT_LOGGING_IN_DELAY_TITLE"));
    mw_isMiddleClickEnabledCheckBox->setText(tr("CHECK_BOX_IS_MIDDLE_CLICK_ENABLED_TEXT"));
    mw_isMiddleClickDoubleCheckBox->setText(tr("CHECK_BOX_IS_MIDDLE_CLICK_DOUBLE_TEXT"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    setLayout(layout);
    reset();

    connect(mw_resetPushButton, &QPushButton::clicked, this, &ReloginSettingsWidget::reset);
}

void ReloginSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    mr_model.setEnabled(mw_isEnabledCheckBox->isChecked());
    mr_model.setReloginPeriod(mw_reloginPeriodInput->get());
    mr_model.setCancelPoint(mw_cancelPointInput->get());
    mr_model.setMenuPoint(mw_menuPointInput->get());
    mr_model.setRestartPoint(mw_restartPointInput->get());
    mr_model.setConfirmPoint(mw_confirmPointInput->get());
    mr_model.setStartPoint(mw_startPointInput->get());
    mr_model.setSitPoint(mw_sitPointInput->get());
    mr_model.setLoggingOutDelay(mw_loggingOutDelayInput->get());
    mr_model.setLoggingInDelay(mw_loggingInDelayInput->get());
    mr_model.setMiddleClickEnabled(mw_isMiddleClickEnabledCheckBox->isChecked());
    mr_model.setMiddleClickDouble(mw_isMiddleClickDoubleCheckBox->isChecked());
}

bool ReloginSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    if (!mw_cancelPointInput->isValid(error)) {
        errorList << tr("ERROR_CANCEL_POINT_INVALID");
        isValid = false;
    }
    if (!mw_menuPointInput->isValid(error)) {
        errorList << tr("ERROR_MENU_POINT_INVALID");
        isValid = false;
    }
    if (!mw_restartPointInput->isValid(error)) {
        errorList << tr("ERROR_RESTART_POINT_INVALID");
        isValid = false;
    }
    if (!mw_confirmPointInput->isValid(error)) {
        errorList << tr("ERROR_CONFIRM_POINT_INVALID");
        isValid = false;
    }
    if (!mw_startPointInput->isValid(error)) {
        errorList << tr("ERROR_START_POINT_INVALID");
        isValid = false;
    }
    if (!mw_sitPointInput->isValid(error)) {
        errorList << tr("ERROR_SIT_POINT_INVALID");
        isValid = false;
    }
    if (!mw_loggingOutDelayInput->isValid(error)) {
        errorList << tr("ERROR_LOGGING_OUT_DELAY_INVALID");
        isValid = false;
    }
    if (!mw_loggingInDelayInput->isValid(error)) {
        errorList << tr("ERROR_LOGGING_IN_DELAY_INVALID");
        isValid = false;
    }
    error += errorList.join("\r\n");
    return isValid;
}

void ReloginSettingsWidget::reset()
{
    mw_isEnabledCheckBox->setChecked(mr_model.isEnabled());
    mw_reloginPeriodInput->set(mr_model.getReloginPeriod());
    mw_cancelPointInput->set(mr_model.getCancelPoint());
    mw_menuPointInput->set(mr_model.getMenuPoint());
    mw_restartPointInput->set(mr_model.getRestartPoint());
    mw_confirmPointInput->set(mr_model.getConfirmPoint());
    mw_startPointInput->set(mr_model.getStartPoint());
    mw_sitPointInput->set(mr_model.getSitPoint());
    mw_loggingOutDelayInput->set(mr_model.getLoggingOutDelay());
    mw_loggingInDelayInput->set(mr_model.getLoggingInDelay());
    mw_isMiddleClickEnabledCheckBox->setChecked(mr_model.isMiddleClickEnabled());
    mw_isMiddleClickDoubleCheckBox->setChecked(mr_model.isMiddleClickDouble());
}
