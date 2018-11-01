#include "widget_settings_window.h"

#include <QGridLayout>
#include <QMessageBox>

#include <stdexcept>

#include "widget_group_box_wrapper.h"
#include "crypto/crypto.h"

WindowSettingsWidget::WindowSettingsWidget(
        WindowModel &model,
        QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_lineageNameLineEdit{new QLineEdit{this}}
    , mw_l2lokiNameLineEdit{new QLineEdit{this}}
    , mw_l2lokiNameRandomizePushButton{new QPushButton{this}}

    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_lineageNameLineEdit),        0, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_l2lokiNameLineEdit),         1, 0);
    layout->addWidget(mw_l2lokiNameRandomizePushButton,                     1, 1);
    layout->addWidget(mw_resetPushButton,                                   2, 0, 1, 2);

    GET_GROUP_BOX_WRAPPER(mw_lineageNameLineEdit)->setTitle(tr("INPUT_LINEAGE_NAME_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_l2lokiNameLineEdit)->setTitle(tr("INPUT_L2LOKI_NAME_TITLE"));
    mw_l2lokiNameRandomizePushButton->setText(tr("PUSH_BUTTON_RANDOMIZE_L2LOKI_NAME_TEXT"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    setLayout(layout);
    setFixedHeight(175);
    reset();

    connect(mw_l2lokiNameRandomizePushButton, &QPushButton::clicked, this, &WindowSettingsWidget::randomizeL2LokiName);
    connect(mw_resetPushButton, &QPushButton::clicked, this, &WindowSettingsWidget::reset);
}

void WindowSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    mr_model.setLineageName(mw_lineageNameLineEdit->text());
    mr_model.setL2LokiName(mw_l2lokiNameLineEdit->text());
}

bool WindowSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    error += errorList.join("\r\n");
    return isValid;
}

void WindowSettingsWidget::randomizeL2LokiName()
{
    mw_l2lokiNameLineEdit->setText(Crypto::randomAlphanumeric(32));
}

void WindowSettingsWidget::reset()
{
    mw_lineageNameLineEdit->setText(mr_model.getLineageName());
    mw_l2lokiNameLineEdit->setText(mr_model.getL2LokiName());
}
