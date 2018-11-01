#pragma once

#include <Windows.h>
#include <stdexcept>

class Device
{

public:
    explicit Device(PCWSTR deviceInterface);
    Device(const Device &) = delete;
    void operator =(const Device &) = delete;
    virtual ~Device() = default;

    virtual void                initialize();
    virtual void                abort();

    virtual bool                isInitialized() const;
    virtual bool                isAborted() const;

protected:
    virtual void                setOutputReport(PVOID data, DWORD size);
    virtual void                getIndexedString(PVOID data, DWORD size);

private:
    PCWSTR                      mp_deviceInterface  {nullptr};
    HANDLE                      mp_deviceHandle     {nullptr};
    bool                        m_isInitialized     {false};
    bool                        m_isAborted         {false};
};
