#include "service_hook.h"

#include <QMutexLocker>

HHOOK                       HookService::s_hook = nullptr;
QList<IObservable *>        HookService::s_observableItemList;
QMutex                      HookService::s_observableItemListMutex;

HookService &HookService::get()
{
    static HookService instance;
    return instance;
}

void HookService::initialize()
{
    if (nullptr != s_hook) {
        throw std::runtime_error{"ERROR_DOUBLE_INITIALIZATION"};
    }
    s_hook = SetWindowsHookEx(WH_KEYBOARD_LL, &HookService::keyboardHookFunction, nullptr, 0);
    if (nullptr == s_hook) {
        throw std::runtime_error{"ERROR_SETTING_ERROR"};
    }
}

void HookService::subscribe(IObservable *item)
{
    s_observableItemList.push_back(item);
}

void HookService::unsubscribe(IObservable *item)
{
    s_observableItemList.removeOne(item);
}

LRESULT HookService::keyboardHookFunction(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (GetKeyState(VK_ESCAPE) & 0x8000) {
        QMutexLocker locker{&s_observableItemListMutex};
        foreach (IObservable *item, s_observableItemList) {
            item->onEvent();
        }
    }
    return CallNextHookEx(s_hook, nCode, wParam, lParam);
}
