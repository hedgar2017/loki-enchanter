#include "service_registry.h"

#include <QString>

const int RegistryService::getMouseSensivity()
{
    DWORD size = 3;
    char buffer[3];

    LONG getValueResult = RegGetValueA(HKEY_CURRENT_USER, "Control Panel\\Mouse", "MouseSensitivity", RRF_RT_REG_SZ, nullptr, &buffer, &size);
    if (ERROR_SUCCESS != getValueResult) {
        return -1;
    }

    bool ok = false;
    int value = QString{buffer}.toInt(&ok);
    if (!ok) {
        return -1;
    }
    return value;
}

const int RegistryService::getMouseSpeed()
{
    DWORD size = 2;
    char buffer[2];

    LONG getValueResult = RegGetValueA(HKEY_CURRENT_USER, "Control Panel\\Mouse", "MouseSpeed", RRF_RT_REG_SZ, nullptr, &buffer, &size);
    if (ERROR_SUCCESS != getValueResult) {
        return -1;
    }

    bool ok = false;
    int value = QString{buffer}.toInt(&ok);
    if (!ok) {
        return -1;
    }
    return value;
}
