#include "dialog_settings.h"

#include <QGridLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

#include "widgets/widget_settings_enchant.h"
#include "widgets/widget_settings_ocr.h"
#include "widgets/widget_settings_macro.h"
#include "widgets/widget_settings_relogin.h"
#include "widgets/widget_settings_window.h"
#include "widgets/widget_settings_device.h"
#include "widgets/widget_settings_locale.h"
#include "interfaces/i_applyable.h"
#include "services/service_storage.h"

SettingsDialog::SettingsDialog(
        std::shared_ptr<Application> p_app,
        QWidget *parent)
    : mp_app{p_app}
    , QDialog{parent}

    , mw_tabWidget{new QTabWidget{this}}

    , mw_savePushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(mw_tabWidget,         0, 0);
    layout->addWidget(mw_savePushButton,    1, 0);

    mw_tabWidget->addTab(
                new EnchantSettingsWidget{mp_app->getEnchantModel(),  this},
                QIcon{":/icons/settings_enchant"},
                tr("TAB_ENCHANT")
                );
    mw_tabWidget->addTab(
                new OCRSettingsWidget{mp_app->getOcrModel(), this},
                QIcon{":/icons/settings_ocr"},
                tr("TAB_OCR")
                );
    mw_tabWidget->addTab(
                new MacroSettingsWidget{mp_app->getMacroModel(), this},
                QIcon{":/icons/settings_macro"},
                tr("TAB_MACRO")
                );
    mw_tabWidget->addTab(
                new ReloginSettingsWidget{mp_app->getReloginModel(), this},
                QIcon{":/icons/settings_relogin"},
                tr("TAB_RELOGIN")
                );
    mw_tabWidget->addTab(
                new DeviceSettingsWidget{this},
                QIcon{":/icons/settings_device"},
                tr("TAB_DEVICE")
                );
    mw_tabWidget->addTab(
                new WindowSettingsWidget{mp_app->getWindowModel(), this},
                QIcon{":/icons/settings_window"},
                tr("TAB_WINDOW")
                );
    mw_tabWidget->addTab(
                new LocaleSettingsWidget{mp_app->getLocaleModel(), this},
                QIcon{":/icons/settings_locale"},
                tr("TAB_LOCALE")
                );
    mw_savePushButton->setText(tr("PUSH_BUTTON_SAVE_TEXT"));

    setLayout(layout);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setWindowIcon(QIcon{":/icons/settings"});
    setWindowTitle(tr("WINDOW_TITLE"));
    adjustSize();
    setFixedSize(750, geometry().height());
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    connect(mw_savePushButton, &QPushButton::clicked, this, &SettingsDialog::accept);
}

void SettingsDialog::accept()
{
    for (int i = 0; i < mw_tabWidget->count(); ++i) {
        IValidable *validable = dynamic_cast<IValidable*>(mw_tabWidget->widget(i));
        if (nullptr == validable) continue;
        QString error;
        if (!validable->isValid(error)) {
            QMessageBox::critical(this, tr("ERROR"), error, QMessageBox::Close);
            return;
        }
    }

    for (int i = 0; i < mw_tabWidget->count(); ++i) {
        IApplyable *applyable = dynamic_cast<IApplyable*>(mw_tabWidget->widget(i));
        if (nullptr == applyable) continue;
        try {
            applyable->apply();
        } catch (const std::runtime_error &e) {
            QMessageBox::critical(this, tr("ERROR"), e.what(), QMessageBox::Close);
            return;
        }
    }
    QDialog::accept();
}
