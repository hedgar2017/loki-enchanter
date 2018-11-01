#pragma once

#include <QString>

class IValidable
{

public:
    virtual bool isValid(QString &error) const = 0;
};
