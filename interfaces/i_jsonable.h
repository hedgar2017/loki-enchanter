#pragma once

#include <QJsonObject>

class IJsonable
{

public:
    virtual QJsonObject toJson() const = 0;
};
