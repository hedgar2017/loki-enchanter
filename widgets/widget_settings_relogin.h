#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QCheckBox>
#include <QPushButton>

#include "models/model_relogin.h"
#include "widget_line_edit_input_integer.h"
#include "widget_input_qpoint.h"

class ReloginSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit ReloginSettingsWidget(ReloginModel &, QWidget *parent = nullptr);
    ReloginSettingsWidget(const ReloginSettingsWidget &) = delete;
    void operator =(const ReloginSettingsWidget &) = delete;
    virtual ~ReloginSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            reset();

private:
    ReloginModel                    &mr_model;

    QCheckBox                       *mw_isEnabledCheckBox;
    IntegerInputLineEdit            *mw_reloginPeriodInput;
    QPointInputWidget               *mw_cancelPointInput;
    QPointInputWidget               *mw_menuPointInput;
    QPointInputWidget               *mw_restartPointInput;
    QPointInputWidget               *mw_confirmPointInput;
    QPointInputWidget               *mw_startPointInput;
    QPointInputWidget               *mw_sitPointInput;
    IntegerInputLineEdit            *mw_loggingInDelayInput;
    IntegerInputLineEdit            *mw_loggingOutDelayInput;
    QCheckBox                       *mw_isMiddleClickEnabledCheckBox;
    QCheckBox                       *mw_isMiddleClickDoubleCheckBox;

    QPushButton                     *mw_resetPushButton;
};
