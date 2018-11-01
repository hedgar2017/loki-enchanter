#include "service_devcon.h"

#include <QProcess>

#include "services/service_storage.h"

void DevconService::installDevice()
{
    const QString &path = StorageService::pathDriver();

    QProcess process;
    process.start(path + "devcon.exe", QStringList{} << "install" << path + "hidriver.inf" << "root\\hidriver", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
}

void DevconService::uninstallDevice()
{
    const QString &path = StorageService::pathDriver();

    QProcess process;
    process.start(path + "devcon.exe", QStringList{} << "remove" << path + "hidriver.inf" << "root\\hidriver", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
}

bool DevconService::isDeviceInstalled()
{
    const QString &path = StorageService::pathDriver();

    QProcess process;
    process.start(path + "devcon.exe", QStringList{} << "status" << "root\\hidriver", QProcess::ReadOnly);
    process.waitForFinished();
    QString output{process.readAllStandardOutput()};
    if (EXIT_SUCCESS != process.exitCode()) {
        throw std::runtime_error{output.toStdString()};
    }
    foreach (const QString &s, output.split(QRegExp{"[\r\n]"}, QString::SkipEmptyParts)) {
        if (s.contains("Driver is running.")) {
            return true;
        }
    }
    return false;
}
