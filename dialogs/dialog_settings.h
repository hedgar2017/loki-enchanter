#pragma once

#include <QDialog>
#include <QPointer>
#include <QTabWidget>
#include <QPushButton>

#include "application.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(std::shared_ptr<Application> p_app, QWidget *parent = nullptr);
    SettingsDialog(const SettingsDialog &) = delete;
    void operator =(const SettingsDialog &) = delete;
    virtual ~SettingsDialog() override = default;

private slots:
    void                            accept() override;

private:
    std::shared_ptr<Application>    mp_app;

    QTabWidget                      *mw_tabWidget;
    QPushButton                     *mw_savePushButton;
};
