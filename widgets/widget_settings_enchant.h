#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>

#include "models/model_enchant.h"
#include "widget_line_edit_input_integer.h"

class EnchantSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit EnchantSettingsWidget(EnchantModel &, QWidget *parent = nullptr);
    EnchantSettingsWidget(const EnchantSettingsWidget &) = delete;
    void operator =(const EnchantSettingsWidget &) = delete;
    virtual ~EnchantSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            reset();

private:
    EnchantModel                    &mr_model;

    IntegerInputLineEdit            *mw_itemAmountInput;
    IntegerInputLineEdit            *mw_skipItemsInput;
    IntegerInputLineEdit            *mw_itemLevelInput;
    IntegerInputLineEdit            *mw_scrollCooldownInput;
    IntegerInputLineEdit            *mw_delayBeforeStartInput;
    QTextEdit                       *mw_itemSignatureListTextEdit;
    QCheckBox                       *mw_isGlobalStopHookEnabledCheckBox;

    QPushButton                     *mw_resetPushButton;
};
