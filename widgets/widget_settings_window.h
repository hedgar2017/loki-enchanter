#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QLineEdit>
#include <QPushButton>

#include "models/model_window.h"

class WindowSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit WindowSettingsWidget(WindowModel &, QWidget *parent = nullptr);
    WindowSettingsWidget(const WindowSettingsWidget &) = delete;
    void operator =(const WindowSettingsWidget &) = delete;
    virtual ~WindowSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            randomizeL2LokiName();
    void                            reset();

private:
    WindowModel                     &mr_model;

    QLineEdit                       *mw_lineageNameLineEdit;
    QLineEdit                       *mw_l2lokiNameLineEdit;
    QPushButton                     *mw_l2lokiNameRandomizePushButton;

    QPushButton                     *mw_resetPushButton;
};
