#include "service_storage.h"

#include <QCoreApplication>

const QString StorageService::pathLogs()
{
    return QCoreApplication::applicationDirPath() + "/logs/";
}

const QString StorageService::pathProfiles()
{
    return QCoreApplication::applicationDirPath() + "/profiles/";
}

const QString StorageService::pathTessdata()
{
    return QCoreApplication::applicationDirPath() + "/tessdata/";
}

const QString StorageService::pathDriver()
{
    return QCoreApplication::applicationDirPath() + "/driver/";
}
