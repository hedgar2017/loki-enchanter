#include "thread_enchant_interlude.h"

#include <QTime>
#include <stdexcept>

#include "services/service_hook.h"
#include "screenshot/screenshot.h"
#include "ocr/ocr_processed.h"

InterludeEnchantThread::InterludeEnchantThread(const std::shared_ptr<Application> &p_app, QObject *parent)
    : EnchantThread{parent}
    , mp_app{p_app}
    , mp_mouse{nullptr}
    , mp_ocr{nullptr}

    , m_currentItem{mp_app->getEnchantModel().getSkipItems()}
    , m_currentLevel{ITEM_LEVEL_INVALID}
{}

void InterludeEnchantThread::run()
{
    if (isInitialized()) {
        sendReport(tr("ERROR_DOUBLE_INITIALIZATION"));
        return;
    }

    mp_mouse.reset(new Mouse);
    try {
        sendReport(tr("MESSAGE_MOUSE_INITIALIZATION"));
        mp_mouse->initialize();
    } catch (const std::runtime_error &e) {
        abort();
        sendReport(tr("ERROR_MOUSE").arg(e.what()));
        return;
    }

    mp_ocr.reset(new ProcessedOCR{});
    try {
        sendReport(tr("MESSAGE_OCR_INITIALIZATION"));
        mp_ocr->initialize();
    } catch (const std::runtime_error &e) {
        abort();
        sendReport(tr("ERROR_OCR").arg(e.what()));
        return;
    }

    int delay = mp_app->getEnchantModel().getDelayBeforeStart();
    sendReport(tr("MESSAGE_JOB_STARTED").arg(QString::number(delay)));
    sleepInterruptible(delay);

    if (mp_app->getEnchantModel().isGlobalStopHookEnabled()) {
        HookService::get().subscribe(this);
    }

    static QTime reloginTimer;
    static bool isReloginTimerStarted = false;
    if (mp_app->getReloginModel().isEnabled() && !isReloginTimerStarted) {
        reloginTimer.start();
        isReloginTimerStarted = true;
    }
    QTime cooldownTimer;

    while (!isAborted() && m_currentItem < mp_app->getEnchantModel().getItemAmount()) {
        try {
            moveCursor(mp_app->getMacroModel().getScrollPoint());
            mp_mouse->leftButtonClick();
            QThread::msleep(mp_app->getMacroModel().getScrollPointDelay());
            moveCursor(getItemPoint());

            if (m_currentLevel < 0 || m_currentLevel >= mp_app->getEnchantModel().getItemLevel()) {
                QThread::msleep(mp_app->getMacroModel().getItemPointDelay());
                m_currentLevel = getCurrentItemLevel();
                if (ITEM_LEVEL_INVALID == m_currentLevel) {
                    sendReport(tr("MESSAGE_ITEM_LEVEL_INVALID"));
                    continue;
                }
                if (m_currentLevel >= mp_app->getEnchantModel().getItemLevel()) {
                    m_currentItem++;
                    m_currentLevel = ITEM_LEVEL_INVALID;
                    sendReport(tr("MESSAGE_ITEM_FINISHED").arg(QString::number(m_currentItem)));
                    continue;
                }
                int diff = mp_app->getEnchantModel().getItemLevel() - m_currentLevel;
                sendReport(tr("MESSAGE_ITEM_LEVEL_RECOGNIZED").arg(QString::number(m_currentLevel), QString::number(diff)));
            } else {
                QThread::msleep(GENERIC_DELAY_MS);
            }

            if (ITEM_LEVEL_INVALID != m_currentLevel && m_currentLevel < mp_app->getEnchantModel().getItemLevel()) {
                mp_mouse->leftButtonClick();
                QThread::msleep(GENERIC_DELAY_MS);
                moveCursor(mp_app->getMacroModel().getConfirmPoint());
                QThread::msleep(GENERIC_DELAY_MS);
                mp_mouse->leftButtonClick();
                int msecsToCooldown = mp_app->getEnchantModel().getScrollCooldown() - cooldownTimer.elapsed();
                if (msecsToCooldown > 0) {
                    sleepInterruptible(msecsToCooldown);
                }
                cooldownTimer.restart();
                QThread::msleep(GENERIC_DELAY_MS);

                ++m_currentLevel;
            }

            if (mp_app->getReloginModel().isEnabled() && reloginTimer.elapsed() >= mp_app->getReloginModel().getReloginPeriod() * 60 * 1E3) {
                relogin();
                reloginTimer.restart();
            }
        } catch (const std::runtime_error &e) {
            if (!isAborted()) {
                sendReport(tr("ERROR_THREAD").arg(e.what()));
                QThread::msleep(GENERIC_DELAY_MS);
            }
        }
    }

    abort();
    sendReport(tr("MESSAGE_JOB_FINISHED"));
}

void InterludeEnchantThread::initialize()
{
    EnchantThread::initialize();
}

void InterludeEnchantThread::abort()
{
    if (isAborted()) return;
    EnchantThread::abort();

    if (mp_app->getEnchantModel().isGlobalStopHookEnabled()) {
        HookService::get().unsubscribe(this);
    }
    mp_mouse->abort();
}

void InterludeEnchantThread::onEvent()
{
    abort();
}

int InterludeEnchantThread::getCurrentItemLevel()
{
    QRect itemLevelRect = mp_app->getOcrModel().getScreenshotRectangle();
    itemLevelRect.setX(itemLevelRect.x() + ITEM_HORIZONTAL_OFFSET * (m_currentItem % ITEMS_IN_A_ROW));
    itemLevelRect.setY(itemLevelRect.y() + ITEM_VERTICAL_OFFSET * (m_currentItem / ITEMS_IN_A_ROW));
    itemLevelRect.setWidth(mp_app->getOcrModel().getScreenshotRectangle().width());
    itemLevelRect.setHeight(mp_app->getOcrModel().getScreenshotRectangle().height());

    QPixmap screenshot = Screenshot::make(itemLevelRect);
    QString tesseractOutput = mp_ocr->recognize(ProcessedOCR::pixmapToProcessedImage(screenshot)).trimmed();
    sendPreview(screenshot, tesseractOutput);

    if (tesseractOutput.isEmpty()) {
        return ITEM_LEVEL_INVALID;
    }

    if ('+' == tesseractOutput[0]) {
        QString levelSubstring;
        for (int i = 1; i < tesseractOutput.size() && tesseractOutput[i].isDigit(); ++i) {
            levelSubstring.append(tesseractOutput[i]);
        }

        bool ok = false;
        int level = levelSubstring.toInt(&ok);
        return (ok ? level : ITEM_LEVEL_INVALID);
    } else {
        return (mp_app->getEnchantModel().isSignaturePresent(tesseractOutput) ? ITEM_LEVEL_ZERO : ITEM_LEVEL_INVALID);
    }
}

QPoint InterludeEnchantThread::getItemPoint() const
{
    return QPoint{
                mp_app->getMacroModel().getItemPoint().x() + ITEM_HORIZONTAL_OFFSET * (m_currentItem % ITEMS_IN_A_ROW),
                mp_app->getMacroModel().getItemPoint().y() + ITEM_VERTICAL_OFFSET * (m_currentItem / ITEMS_IN_A_ROW)
    };
}

void InterludeEnchantThread::moveCursor(const QPoint &point)
{
    mp_mouse->moveCursor(point.x(), point.y());
}

void InterludeEnchantThread::relogin()
{
    int logOutDelay = mp_app->getReloginModel().getLoggingOutDelay();
    int logInDelay = mp_app->getReloginModel().getLoggingInDelay();

    QThread::msleep(GENERIC_DELAY_MS);

    sendReport(tr("MESSAGE_RELOGIN_CANCEL"));
    moveCursor(mp_app->getReloginModel().getCancelPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    QThread::msleep(GENERIC_DELAY_MS);

    sendReport(tr("MESSAGE_RELOGIN_MENU"));
    moveCursor(mp_app->getReloginModel().getMenuPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    QThread::msleep(GENERIC_DELAY_MS);

    sendReport(tr("MESSAGE_RELOGIN_RESTART"));
    moveCursor(mp_app->getReloginModel().getRestartPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    QThread::msleep(GENERIC_DELAY_MS);

    sendReport(tr("MESSAGE_RELOGIN_CONFIRM"));
    moveCursor(mp_app->getReloginModel().getConfirmPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    sendReport(tr("MESSAGE_RELOGIN_LOGGING_OUT_SLEEP").arg(QString::number(logOutDelay)));
    sleepInterruptible(logOutDelay);
    if (isAborted()) return;

    sendReport(tr("MESSAGE_RELOGIN_START"));
    moveCursor(mp_app->getReloginModel().getStartPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    sendReport(tr("MESSAGE_RELOGIN_LOGGING_IN_SLEEP").arg(QString::number(logInDelay)));
    sleepInterruptible(logInDelay);
    if (isAborted()) return;

    if (mp_app->getReloginModel().isMiddleClickEnabled()) {
        mp_mouse->middleButtonClick();
        QThread::msleep(GENERIC_DELAY_MS);
        if (mp_app->getReloginModel().isMiddleClickDouble()) {
            mp_mouse->middleButtonClick();
            QThread::msleep(GENERIC_DELAY_MS);
        }
    }

    sendReport(tr("MESSAGE_RELOGIN_SIT"));
    moveCursor(mp_app->getReloginModel().getSitPoint());
    QThread::msleep(GENERIC_DELAY_MS);
    mp_mouse->leftButtonClick();
    QThread::msleep(GENERIC_DELAY_MS);
}

void InterludeEnchantThread::sendReport(const QString &message)
{
    emit reportSent(Report{
                        m_currentItem,
                        mp_app->getEnchantModel().getItemAmount(),
                        message,
                        isAborted() || m_currentItem >= mp_app->getEnchantModel().getItemAmount()
                    });
}

void InterludeEnchantThread::sendPreview(const QPixmap &pixmap, const QString &text)
{
    emit previewSent(Preview{pixmap, text});
}
