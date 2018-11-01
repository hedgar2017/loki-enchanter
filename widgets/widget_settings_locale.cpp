#include "widget_settings_locale.h"

#include <QGridLayout>
#include <QMessageBox>

#include <stdexcept>

#include "widget_group_box_wrapper.h"

LocaleSettingsWidget::LocaleSettingsWidget(
        LocaleModel &model,
        QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_nameComboBox{new QComboBox{this}}

    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_nameComboBox),       0, 0);
    layout->addWidget(mw_resetPushButton,                           1, 0);

    GET_GROUP_BOX_WRAPPER(mw_nameComboBox)->setTitle(tr("COMBO_BOX_NAME_TITLE"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    mw_nameComboBox->addItem(QIcon{":/icons/language_en_US"}, tr("LOCALE_ENGLISH_TEXT"), "en_US");
    mw_nameComboBox->addItem(QIcon{":/icons/language_ru_RU"}, tr("LOCALE_RUSSIAN_TEXT"), "ru_RU");
    mw_nameComboBox->addItem(QIcon{":/icons/language_uk_UA"}, tr("LOCALE_UKRAINIAN_TEXT"), "uk_UA");

    setLayout(layout);
    setFixedHeight(100);
    reset();

    connect(mw_resetPushButton, &QPushButton::clicked, this, &LocaleSettingsWidget::reset);
}

void LocaleSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    switch (mw_nameComboBox->currentIndex()) {
    case LOCALE_ID_en_US:
        mr_model.setName("en_US");
        break;
    case LOCALE_ID_ru_RU:
        mr_model.setName("ru_RU");
        break;
    case LOCALE_ID_uk_UA:
        mr_model.setName("uk_UA");
        break;
    default:
        return;
    }
}

bool LocaleSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    error += errorList.join("\r\n");
    return isValid;
}

void LocaleSettingsWidget::reset()
{
    if (mr_model.getName() == "en_US") {
        mw_nameComboBox->setCurrentIndex(LOCALE_ID_en_US);
    } else if (mr_model.getName() == "ru_RU") {
        mw_nameComboBox->setCurrentIndex(LOCALE_ID_ru_RU);
    } else if (mr_model.getName() == "uk_UA") {
        mw_nameComboBox->setCurrentIndex(LOCALE_ID_uk_UA);
    } else {
        mw_nameComboBox->setCurrentIndex(LOCALE_ID_en_US);
    }
}
