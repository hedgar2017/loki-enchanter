#include "service_bcdedit.h"

#include <QProcess>

void BCDEditService::enableTestMode()
{
    QProcess process;
    process.start("bcdedit.exe", QStringList{} << "/set" << "testsigning" << "on", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
}

void BCDEditService::disableTestMode()
{
    QProcess process;
    process.start("bcdedit.exe", QStringList{} << "/set" << "testsigning" << "off", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
}

bool BCDEditService::isTestModeEnabled()
{
    QProcess process;
    process.start("bcdedit.exe", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
    foreach (const QString &s, output.split(QRegExp{"[\r\n]"}, QString::SkipEmptyParts)) {
        if (s.contains("testsigning") && s.contains("Yes")) {
            return true;
        }
    }
    return false;
}
