#pragma once

class IObservable
{

public:
    virtual void onEvent() = 0;
};
