#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>
#include <QTranslator>
#include <QPointer>
#include <QSharedPointer>

#include "application.h"
#include "threads/thread_enchant.h"
#include "widgets/widget_progress_bar_item.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow &) = delete;
    void operator =(const MainWindow &) = delete;
    virtual ~MainWindow() = default;

protected:
    void                        changeEvent(QEvent *);
    void                        closeEvent(QCloseEvent *);

private slots:
    void                        onSave();
    void                        onSaveAs();
    void                        onOpen();
    void                        onSettings();

    void                        onEnchantStart();
    void                        onEnchantStop();

    void                        onLineageWindowMove();
    void                        onApplicationWindowRename();

    void                        onAboutOpen();

    void                        onReportReceive(const EnchantThread::Report &);
    void                        onPreviewReceive(const EnchantThread::Preview &);

private:
    QWidget                     *createCentralWidget();
    QMenuBar                    *createMenuBar();

    bool                        isApplicationChanged() const;

    void                        update();
    void                        setLocale(const QString &name);

    std::shared_ptr<Application>    mp_application;
    QPointer<EnchantThread>         mp_enchantThread;

    QTranslator                     m_appTranslator;
    QTranslator                     m_qtTranslator;

    QMenu                           *mw_mainMenu;
    QAction                         *mp_mainSaveAction;
    QAction                         *mp_mainSaveAsAction;
    QAction                         *mp_mainOpenAction;
    QAction                         *mp_mainSettingsAction;
    QAction                         *mp_mainCloseAction;

    QMenu                           *mw_enchantMenu;
    QAction                         *mp_enchantStartAction;
    QAction                         *mp_enchantStopAction;

    QMenu                           *mw_windowMenu;
    QAction                         *mp_lineageWindowMoveAction;
    QAction                         *mp_applicationWindowRenameAction;

    QMenu                           *mw_infoMenu;
    QAction                         *mp_aboutDialogOpenAction;

    ItemProgressBar                 *mw_itemProgressBar;
    QGraphicsView                   *mw_previewImageGraphicsView;
    QTextEdit                       *mw_previewTextEdit;
    QPushButton                     *mw_startPushButton;
    QPushButton                     *mw_stopPushButton;
};
