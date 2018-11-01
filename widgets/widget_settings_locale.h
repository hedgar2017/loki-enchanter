#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QComboBox>
#include <QPushButton>

#include "models/model_locale.h"

class LocaleSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit LocaleSettingsWidget(LocaleModel &, QWidget *parent = nullptr);
    LocaleSettingsWidget(const LocaleSettingsWidget &) = delete;
    void operator =(const LocaleSettingsWidget &) = delete;
    virtual ~LocaleSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            reset();

private:
    enum Locale {
        LOCALE_ID_en_US = 0,
        LOCALE_ID_ru_RU = 1,
        LOCALE_ID_uk_UA = 2
    };

    LocaleModel                     &mr_model;

    QComboBox                       *mw_nameComboBox;

    QPushButton                     *mw_resetPushButton;
};
