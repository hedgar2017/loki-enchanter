#include "device.h"

#include <cfgmgr32.h>
#include <hidsdi.h>

Device::Device(PCWSTR deviceInterface)
    : mp_deviceInterface(deviceInterface)
{}

void Device::initialize()
{
    if (isInitialized()) throw std::runtime_error{"ERROR_DOUBLE_INITIALIZATION"};

    GUID guid;
    HidD_GetHidGuid(&guid);

    ULONG deviceInterfaceListLength = 0;
    CONFIGRET configret = CM_Get_Device_Interface_List_Size(
        &deviceInterfaceListLength,
        &guid,
        nullptr,
        CM_GET_DEVICE_INTERFACE_LIST_PRESENT
    );
    if (CR_SUCCESS != configret) {
        throw std::runtime_error{"ERROR_DEVICE_01"};
    }

    if (deviceInterfaceListLength <= 1) {
        throw std::runtime_error{"ERROR_DEVICE_02"};
    }

    PWSTR deviceInterfaceList = (PWSTR) malloc(deviceInterfaceListLength * sizeof(WCHAR));
    if (nullptr == deviceInterfaceList) {
        throw std::runtime_error{"ERROR_DEVICE_03"};
    }
    ZeroMemory(deviceInterfaceList, deviceInterfaceListLength * sizeof(WCHAR));

    configret = CM_Get_Device_Interface_List(
        &guid,
        nullptr,
        deviceInterfaceList,
        deviceInterfaceListLength,
        CM_GET_DEVICE_INTERFACE_LIST_PRESENT
    );
    if (CR_SUCCESS != configret) {
        free(deviceInterfaceList);
        throw std::runtime_error{"ERROR_DEVICE_04"};
    }

    size_t deviceInterfaceLength = wcslen(mp_deviceInterface);
    HANDLE file = INVALID_HANDLE_VALUE;
    for (PWSTR currentInterface = deviceInterfaceList; *currentInterface; currentInterface += wcslen(currentInterface) + 1) {
        if (0 != wcsncmp(currentInterface, mp_deviceInterface, deviceInterfaceLength)) {
            continue;
        }

        file = CreateFile(currentInterface, GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
        if (INVALID_HANDLE_VALUE == file) {
            continue;
        }

        break;
    }
    free(deviceInterfaceList);
    if (INVALID_HANDLE_VALUE == file) {
        throw std::runtime_error{"ERROR_DEVICE_05"};
    }

    mp_deviceHandle = file;
    m_isInitialized = true;
}

bool Device::isInitialized() const
{
    return m_isInitialized;
}

bool Device::isAborted() const
{
    return m_isAborted;
}

void Device::abort()
{
    if (nullptr != mp_deviceHandle && INVALID_HANDLE_VALUE != mp_deviceHandle) {
        CloseHandle(mp_deviceHandle);
    }
    m_isAborted = true;
}

void Device::setOutputReport(PVOID data, DWORD size)
{
    if (!HidD_SetOutputReport(mp_deviceHandle, data, size)) {
        throw std::runtime_error{"ERROR_DEVICE_06"};
    }
}

void Device::getIndexedString(PVOID data, DWORD size)
{
    ZeroMemory(data, size);
    if (!HidD_GetIndexedString(mp_deviceHandle, 0, data, size)) {
        throw std::runtime_error{"ERROR_DEVICE_07"};
    }
}
