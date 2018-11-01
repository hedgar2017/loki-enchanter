#include "widget_settings_device.h"

#include <QGridLayout>
#include <QMessageBox>
#include <Windows.h>

#include "dialogs/dialog_confirm_reboot.h"
#include "services/service_bcdedit.h"
#include "services/service_devcon.h"

DeviceSettingsWidget::DeviceSettingsWidget(QWidget *parent)
    : QWidget{parent}

    , mw_installPushButton{new QPushButton{this}}
    , mw_checkPushButton{new QPushButton{this}}
    , mw_uninstallPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(mw_installPushButton,         0, 0);
    layout->addWidget(mw_checkPushButton,           1, 0);
    layout->addWidget(mw_uninstallPushButton,       2, 0);

    mw_installPushButton->setText(tr("PUSH_BUTTON_INSTALL_TEXT"));
    mw_checkPushButton->setText(tr("PUSH_BUTTON_CHECK_TEXT"));
    mw_uninstallPushButton->setText(tr("PUSH_BUTTON_UNINSTALL_TEXT"));

    setLayout(layout);
    setFixedHeight(150);

    connect(mw_installPushButton, &QPushButton::clicked, this, &DeviceSettingsWidget::install);
    connect(mw_checkPushButton, &QPushButton::clicked, this, &DeviceSettingsWidget::check);
    connect(mw_uninstallPushButton, &QPushButton::clicked, this, &DeviceSettingsWidget::uninstall);
}

void DeviceSettingsWidget::install()
{
    try {
        if (!BCDEditService::isTestModeEnabled()) {
            if (RebootConfirmDialog::YES != RebootConfirmDialog{this}.exec()) {
                return;
            }
            BCDEditService::enableTestMode();
            if (S_OK != RegisterApplicationRestart(nullptr, 0)) {
                wchar_t buffer[256];
                FormatMessageW(
                            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            nullptr,
                            GetLastError(),
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            buffer,
                            (sizeof(buffer) / sizeof(wchar_t)),
                            nullptr
                            );
                throw std::runtime_error{QString::fromWCharArray(buffer).toStdString()};
            }

            HANDLE processHandle;
            TOKEN_PRIVILEGES tokenPriviledges;
            OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &processHandle);
            LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tokenPriviledges.Privileges[0].Luid);
            tokenPriviledges.PrivilegeCount = 1;
            tokenPriviledges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (!AdjustTokenPrivileges(processHandle, FALSE, &tokenPriviledges, 0, nullptr, nullptr)) {
                wchar_t buffer[256];
                FormatMessageW(
                            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            nullptr,
                            GetLastError(),
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            buffer,
                            (sizeof(buffer) / sizeof(wchar_t)),
                            nullptr
                            );
                throw std::runtime_error{QString::fromWCharArray(buffer).toStdString()};
            }

            if (ERROR_SUCCESS != InitiateShutdownW(
                        nullptr, nullptr, 0,
                        SHUTDOWN_RESTART | SHUTDOWN_RESTARTAPPS,
                        SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_INSTALLATION | SHTDN_REASON_FLAG_PLANNED)
                    ) {
                wchar_t buffer[256];
                FormatMessageW(
                            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            nullptr,
                            GetLastError(),
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            buffer,
                            (sizeof(buffer) / sizeof(wchar_t)),
                            nullptr
                            );
                throw std::runtime_error{QString::fromWCharArray(buffer).toStdString()};
            }
            return;
        }
        if (DevconService::isDeviceInstalled()) {
            throw std::runtime_error{tr("ERROR_ALREADY_INSTALLED").toStdString()};
        }
        DevconService::installDevice();
        QMessageBox::information(this, tr("TITLE_DEVICE_INSTALL"), tr("SUCCESS_DEVICE_INSTALL"), QMessageBox::Close);
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_DEVICE_INSTALL").arg(e.what()), QMessageBox::Close);
    }
}

void DeviceSettingsWidget::check()
{
    try {
        if (DevconService::isDeviceInstalled()) {
            QMessageBox::information(this, tr("TITLE_DEVICE_CHECK"), tr("SUCCESS_DEVICE_CHECK_OK"), QMessageBox::Close);
        } else {
            QMessageBox::information(this, tr("TITLE_DEVICE_CHECK"), tr("SUCCESS_DEVICE_CHECK_ERROR"), QMessageBox::Close);
        }
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_DEVICE_CHECK").arg(e.what()), QMessageBox::Close);
    }
}

void DeviceSettingsWidget::uninstall()
{
    try {        
        if (!DevconService::isDeviceInstalled()) {
            throw std::runtime_error{tr("ERROR_NOT_INSTALLED").toStdString()};
        }
        DevconService::uninstallDevice();
        QMessageBox::information(this, tr("TITLE_DEVICE_UNINSTALL"), tr("SUCCESS_DEVICE_UNINSTALL"), QMessageBox::Close);
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_DEVICE_UNINSTALL").arg(e.what()), QMessageBox::Close);
    }
}
