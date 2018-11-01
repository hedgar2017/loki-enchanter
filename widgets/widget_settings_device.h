#pragma once

#include <QWidget>

#include <QPushButton>

class DeviceSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceSettingsWidget(QWidget *parent = nullptr);
    DeviceSettingsWidget(const DeviceSettingsWidget &) = delete;
    void operator =(const DeviceSettingsWidget &) = delete;
    virtual ~DeviceSettingsWidget() = default;

private slots:
    void            install();
    void            check();
    void            uninstall();

private:
    QPushButton     *mw_installPushButton;
    QPushButton     *mw_checkPushButton;
    QPushButton     *mw_uninstallPushButton;
};
