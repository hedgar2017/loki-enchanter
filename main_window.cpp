#include "main_window.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QStatusBar>
#include <QFileDialog>
#include <QGridLayout>
#include <QCloseEvent>
#include <QScreen>
#include <QJsonDocument>
#include <QLibraryInfo>

#include "services/service_hook.h"
#include "services/service_storage.h"
#include "threads/thread_enchant_interlude.h"
#include "widgets/widget_group_box_wrapper.h"
#include "widgets/widget_settings_window.h"
#include "dialogs/dialog_settings.h"
#include "dialogs/dialog_about.h"
#include "dialogs/dialog_confirm_save.h"
#include "crypto/crypto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , mp_application{nullptr}
    , mp_enchantThread{nullptr}

    , mw_itemProgressBar{new ItemProgressBar{this}}
    , mw_previewImageGraphicsView{new QGraphicsView{this}}
    , mw_previewTextEdit{new QTextEdit{this}}
    , mw_startPushButton{new QPushButton{this}}
    , mw_stopPushButton{new QPushButton{this}}
{
    Application *application = nullptr;
    try {
        application = Application::loadFromFile(StorageService::pathProfiles() + "default.json");
    } catch (const std::runtime_error &) {
        application = new Application;
    }
    mp_application.reset(application);

    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setCentralWidget(createCentralWidget());
    setMenuBar(createMenuBar());
    setLocale(mp_application->getLocaleModel().getName());
    setStatusBar(new QStatusBar{this});

    adjustSize();
    setFixedWidth(300);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    update();

    if (mp_application->getEnchantModel().isGlobalStopHookEnabled()) {
        try {
            HookService::get().initialize();
        } catch (const std::exception &e) {
            QMessageBox::critical(this, tr("ERROR"), tr("ERROR_HOOK").arg(e.what()), QMessageBox::Close);
        }
    }

    qRegisterMetaType<EnchantThread::Report>("EnchantThread::Report");
    qRegisterMetaType<EnchantThread::Preview>("EnchantThread::Preview");
}

QWidget *MainWindow::createCentralWidget()
{
    QWidget *centralWidget = new QWidget{this};

    QGridLayout *layout = new QGridLayout{centralWidget};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemProgressBar),    0, 0, 1, 2);
    layout->addWidget(mw_previewImageGraphicsView,                  1, 0);
    layout->addWidget(mw_previewTextEdit,                           1, 1);
    layout->addWidget(mw_startPushButton,                           2, 0);
    layout->addWidget(mw_stopPushButton,                            2, 1);

    mw_previewImageGraphicsView->setFixedHeight(30);
    mw_previewTextEdit->setFixedHeight(30);
    mw_stopPushButton->setEnabled(false);

    connect(mw_startPushButton, &QPushButton::clicked, this, &MainWindow::onEnchantStart);
    connect(mw_stopPushButton, &QPushButton::clicked, this, &MainWindow::onEnchantStop);

    return centralWidget;
}

QMenuBar *MainWindow::createMenuBar()
{
    mw_mainMenu = new QMenu{this};
    mp_mainOpenAction = mw_mainMenu->addAction(
                QIcon{":/icons/open"},
                QString{},
                this,
                &MainWindow::onOpen,
                QKeySequence{"Ctrl+O"}
                );
    mp_mainSaveAction = mw_mainMenu->addAction(
                QIcon{":/icons/save"},
                QString{},
                this,
                &MainWindow::onSave,
                QKeySequence{"Ctrl+S"}
                );
    mp_mainSaveAsAction = mw_mainMenu->addAction(
                QIcon{":/icons/save"},
                QString{},
                this,
                &MainWindow::onSaveAs,
                QKeySequence{"Ctrl+Shift+S"}
                );
    mw_mainMenu->addSeparator();
    mp_mainSettingsAction = mw_mainMenu->addAction(
                QIcon{":/icons/settings"},
                QString{},
                this,
                &MainWindow::onSettings,
                QKeySequence{"Ctrl+Alt+S"}
                );
    mw_mainMenu->addSeparator();
    mp_mainCloseAction = mw_mainMenu->addAction(
                QIcon{":/icons/close"},
                QString{},
                this,
                &MainWindow::close,
                QKeySequence{"Alt+F4"}
                );

    mw_enchantMenu = new QMenu{this};
    mp_enchantStartAction = mw_enchantMenu->addAction(
                QIcon{":/icons/enchant_start"},
                QString{},
                this,
                &MainWindow::onEnchantStart,
                QKeySequence{"Return"}
                );
    mp_enchantStopAction = mw_enchantMenu->addAction(
                QIcon{":/icons/enchant_stop"},
                QString{},
                this,
                &MainWindow::onEnchantStop,
                QKeySequence{"Esc"}
                );

    mw_windowMenu = new QMenu{this};
    mp_lineageWindowMoveAction = mw_windowMenu->addAction(
                QIcon{":/icons/window_move"},
                QString{},
                this,
                &MainWindow::onLineageWindowMove,
                QKeySequence{"Ctrl+M"}
                );
    mw_windowMenu->addSeparator();
    mp_applicationWindowRenameAction = mw_windowMenu->addAction(
                QIcon{":/icons/window_rename"},
                QString{},
                this,
                &MainWindow::onApplicationWindowRename,
                QKeySequence{"Ctrl+R"}
                );

    mw_infoMenu = new QMenu{this};
    mp_aboutDialogOpenAction = mw_infoMenu->addAction(
                QIcon{":/icons/about"},
                QString{},
                this,
                &MainWindow::onAboutOpen,
                QKeySequence{"F12"}
                );

    mp_enchantStopAction->setEnabled(false);
    mp_mainSaveAction->setEnabled(false);

    QMenuBar *menuBar = new QMenuBar{this};
    menuBar->addMenu(mw_mainMenu);
    menuBar->addMenu(mw_enchantMenu);
    menuBar->addMenu(mw_windowMenu);
    menuBar->addMenu(mw_infoMenu);
    return menuBar;
}

bool MainWindow::isApplicationChanged() const
{
    std::unique_ptr<Application> application;
    try {
        application.reset(Application::loadFromFile(StorageService::pathProfiles() + mp_application->getProfileName()));
    } catch (const std::runtime_error &) {
        return true;
    }
    return *mp_application != *application;
}

void MainWindow::update()
{
    setLocale(mp_application->getLocaleModel().getName());
    setWindowTitle(mp_application->getWindowModel().getL2LokiName());
    mw_itemProgressBar->setData(0, mp_application->getEnchantModel().getSkipItems(), mp_application->getEnchantModel().getItemAmount());
}

void MainWindow::setLocale(const QString &name)
{
    if (m_appTranslator.load(QString{":/translations/%1.qm"}.arg(name))) {
        qApp->installTranslator(&m_appTranslator);
    }
    if (m_qtTranslator.load("qt_" + name, QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        qApp->installTranslator(&m_qtTranslator);
    }
}

void MainWindow::onEnchantStart()
{
    menuBar()->setEnabled(false);
    mp_enchantStartAction->setEnabled(false);
    mw_startPushButton->setEnabled(false);

    mp_enchantThread = new InterludeEnchantThread{mp_application, this};
    connect(mp_enchantThread.data(), &EnchantThread::reportSent, this, &MainWindow::onReportReceive);
    connect(mp_enchantThread.data(), &EnchantThread::previewSent, this, &MainWindow::onPreviewReceive);
    mp_enchantThread->start();

    mp_enchantStopAction->setEnabled(true);
    mw_stopPushButton->setEnabled(true);
}

void MainWindow::onEnchantStop()
{
    mp_enchantStopAction->setEnabled(false);
    mw_stopPushButton->setEnabled(false);

    if (!mp_enchantThread.isNull()) {
        if (!mp_enchantThread->isAborted()) {
            mp_enchantThread->abort();
            mp_enchantThread->wait();
        }
        disconnect(mp_enchantThread.data(), &EnchantThread::reportSent, this, &MainWindow::onReportReceive);
        disconnect(mp_enchantThread.data(), &EnchantThread::previewSent, this, &MainWindow::onPreviewReceive);
        mp_enchantThread.clear();
    }

    if (isApplicationChanged()) {
        mp_mainSaveAction->setEnabled(true);
    }
    menuBar()->setEnabled(true);
    mp_enchantStartAction->setEnabled(true);
    mw_startPushButton->setEnabled(true);
}

void MainWindow::onSave()
{
    QString path = StorageService::pathProfiles() + mp_application->getProfileName();
    if (path.isEmpty()) {
        return;
    }

    try {
        mp_application->saveToFile(path);
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_SAVE").arg(e.what()), QMessageBox::Close);
        return;
    }

    mp_mainSaveAction->setEnabled(false);
    statusBar()->showMessage(tr("STATUS_BAR_MESSAGE_PROFILE_SAVED").arg(mp_application->getProfileName()));
}

void MainWindow::onSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, tr("SAVE_AS_DIALOG_TITLE"), StorageService::pathProfiles(), "JSON (*.json)");
    if (path.isEmpty()) {
        return;
    }

    try {
        mp_application->saveToFile(path);
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_SAVE_AS").arg(e.what()), QMessageBox::Close);
        return;
    }

    mp_mainSaveAction->setEnabled(false);
    statusBar()->showMessage(tr("STATUS_BAR_MESSAGE_PROFILE_SAVED").arg(mp_application->getProfileName()));
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(this, tr("OPEN_DIALOG_TITLE"), StorageService::pathProfiles(), "JSON (*.json)");
    if (path.isEmpty()) {
        return;
    }

    if (mp_mainSaveAction->isEnabled() && SaveConfirmDialog::Status::YES == SaveConfirmDialog{this}.exec()) {
        onSave();
    }

    Application *application = nullptr;
    try {
        application = Application::loadFromFile(path);
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_PROFILE_INVALID").arg(e.what()), QMessageBox::Close);
        return;
    }
    mp_application.reset(application);

    mp_mainSaveAction->setEnabled(false);
    statusBar()->showMessage(tr("STATUS_BAR_MESSAGE_PROFILE_LOADED").arg(mp_application->getProfileName()));
    update();
}

void MainWindow::onSettings()
{
    SettingsDialog{mp_application, this}.exec();
    if (isApplicationChanged()) {
        mp_mainSaveAction->setEnabled(true);
        update();
    }
}

void MainWindow::onAboutOpen()
{
    AboutDialog dialog{this};
    dialog.exec();
}

void MainWindow::onLineageWindowMove()
{
    HWND handle = FindWindow(nullptr, mp_application->getWindowModel().getLineageName().toStdWString().data());
    if (nullptr == handle) {
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_FIND_WINDOW"), QMessageBox::Close);
        return;
    }

    bool result = SetWindowPos(handle, nullptr, 0, 0, -1, -1, SWP_NOSIZE);
    if (!result) {
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
        QMessageBox::critical(this, tr("ERROR"), tr("ERROR_SET_WINDOW_POS").arg(QString::fromWCharArray(buffer)), QMessageBox::Close);
    }
}

void MainWindow::onApplicationWindowRename()
{
    mp_application->getWindowModel().setL2LokiName(Crypto::randomAlphanumeric(32));
    setWindowTitle(mp_application->getWindowModel().getL2LokiName());
}

void MainWindow::onReportReceive(const EnchantThread::Report &report)
{
    mw_itemProgressBar->setData(0, report.currentItem, report.itemAmount);
    mp_application->getEnchantModel().setSkipItems(report.currentItem);
    statusBar()->showMessage(report.message);
    if (report.isAborted) {
        onEnchantStop();
    }
}

void MainWindow::onPreviewReceive(const EnchantThread::Preview &preview)
{
    if (nullptr != mw_previewImageGraphicsView->scene()) {
        delete mw_previewImageGraphicsView->scene();
    }
    mw_previewImageGraphicsView->setScene(new QGraphicsScene());
    mw_previewImageGraphicsView->scene()->addPixmap(preview.pixmap);
    mw_previewTextEdit->setText(preview.text);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (nullptr == event) {
        return;
    }
    switch (event->type()) {
    case QEvent::LocaleChange:
        setLocale(QLocale::system().name());
    case QEvent::LanguageChange:
        GET_GROUP_BOX_WRAPPER(mw_itemProgressBar)->setTitle(tr("PROGRESS_BAR_ITEMS_ENCHANTED_TITLE"));
        mw_startPushButton->setText(tr("PUSH_BUTTON_ENCHANT_START_TEXT"));
        mw_stopPushButton->setText(tr("PUSH_BUTTON_ENCHANT_STOP_TEXT"));

        mw_mainMenu->setTitle(tr("MENU_MAIN_TITLE"));
        mp_mainSaveAction->setText(tr("ACTION_MAIN_SAVE_TEXT"));
        mp_mainSaveAsAction->setText(tr("ACTION_MAIN_SAVE_AS_TEXT"));
        mp_mainOpenAction->setText(tr("ACTION_MAIN_OPEN_TEXT"));
        mp_mainSettingsAction->setText(tr("ACTION_MAIN_SETTINGS_TEXT"));
        mp_mainCloseAction->setText(tr("ACTION_MAIN_QUIT_TEXT"));

        mw_enchantMenu->setTitle(tr("MENU_ENCHANT_TITLE"));
        mp_enchantStartAction->setText(tr("ACTION_ENCHANT_START_TEXT"));
        mp_enchantStopAction->setText(tr("ACTION_ENCHANT_STOP_TEXT"));

        mw_windowMenu->setTitle(tr("MENU_WINDOW_TITLE"));
        mp_lineageWindowMoveAction->setText(tr("ACTION_LINEAGE_WINDOW_MOVE_TEXT"));
        mp_applicationWindowRenameAction->setText(tr("ACTION_APPLICATION_WINDOW_RENAME_TEXT"));

        mw_infoMenu->setTitle(tr("MENU_INFO_TITLE"));
        mp_aboutDialogOpenAction->setText(tr("ACTION_ABOUT_TEXT"));
        break;
    default:
        break;
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    onEnchantStop();
    if (!mp_mainSaveAction->isEnabled()) {
        event->accept();
        return;
    }

    switch (SaveConfirmDialog{this}.exec()) {
    case SaveConfirmDialog::Status::YES:
        onSave();
        event->accept();
        return;
    case SaveConfirmDialog::Status::NO:
        event->accept();
        return;
    case SaveConfirmDialog::Status::CANCEL:
    default:
        event->ignore();
    }
}
