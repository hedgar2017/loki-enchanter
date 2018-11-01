#pragma once

#include <QThread>
#include <QAtomicInt>
#include <QPixmap>

class EnchantThread : public QThread
{
    Q_OBJECT

public:
    struct Report {
        int         currentItem;
        int         itemAmount;
        QString     message;
        bool        isAborted;
    };

    struct Preview {
        QPixmap     pixmap;
        QString     text;
    };

    struct Error {
        QString     text;
    };

    explicit EnchantThread(QObject *parent = nullptr);
    EnchantThread(const EnchantThread &) = delete;
    void operator =(const EnchantThread &) = delete;
    virtual ~EnchantThread() = default;

    virtual void                        run() override = 0;
    virtual void                        initialize() = 0;
    virtual void                        abort() = 0;
    virtual bool                        isInitialized() const;
    virtual bool                        isAborted() const;

signals:
    void                                reportSent(const EnchantThread::Report &);
    void                                previewSent(const EnchantThread::Preview &);
    void                                errorSent(const EnchantThread::Error &);

protected:
    virtual void                        sleepInterruptible(int msecs) const;

private:
    QAtomicInt                          m_isInitialized {0};
    QAtomicInt                          m_isAborted {0};
};
