#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QPushButton>

#include "models/model_macro.h"
#include "widget_line_edit_input_integer.h"
#include "widget_input_qpoint.h"

class MacroSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit MacroSettingsWidget(MacroModel &, QWidget *parent = nullptr);
    MacroSettingsWidget(const MacroSettingsWidget &) = delete;
    void operator =(const MacroSettingsWidget &) = delete;
    virtual ~MacroSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            reset();

private:
    MacroModel                      &mr_model;

    QPointInputWidget               *mw_scrollPointInput;
    QPointInputWidget               *mw_itemPointInput;
    QPointInputWidget               *mw_confirmPointInput;
    IntegerInputLineEdit            *mw_itemPointDelayInput;
    IntegerInputLineEdit            *mw_scrollPointDelayInput;

    QPushButton                     *mw_resetPushButton;
};
