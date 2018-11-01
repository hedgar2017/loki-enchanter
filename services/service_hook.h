#pragma once

#include <Windows.h>
#include <QList>
#include <QMutex>

#include "interfaces/i_observer.h"
#include "interfaces/i_observable.h"

class HookService : public IObserver
{

public:
    static HookService              &get();

    virtual void                    initialize();
    virtual void                    subscribe(IObservable *) override;
    virtual void                    unsubscribe(IObservable *) override;

private:
    explicit HookService() = default;
    HookService(const HookService &) = delete;
    void operator =(const HookService &) = delete;
    virtual ~HookService() = default;

    static LRESULT CALLBACK         keyboardHookFunction(int nCode, WPARAM wParam, LPARAM lParam);

    static HHOOK                    s_hook;
    static QList<IObservable *>     s_observableItemList;
    static QMutex                   s_observableItemListMutex;
};
