#pragma once

#include "i_observable.h"

class IObserver
{

public:
    virtual void subscribe(IObservable *) = 0;
    virtual void unsubscribe(IObservable *) = 0;
};
