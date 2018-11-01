#include "thread_enchant.h"

#include <QTime>

EnchantThread::EnchantThread(QObject *parent)
    : QThread{parent}
{}

void EnchantThread::initialize()
{
    m_isInitialized = 1;
}

void EnchantThread::abort()
{
    m_isAborted = 1;
}

bool EnchantThread::isInitialized() const
{
    return m_isInitialized != 0;
}

bool EnchantThread::isAborted() const
{
    return m_isAborted != 0;
}

void EnchantThread::sleepInterruptible(int msecs) const
{
    QTime time;
    time.start();
    while (!isAborted() && time.elapsed() < msecs) {
        QThread::msleep(10);
    }
}
