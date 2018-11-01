#include "model_window.h"

WindowModel::WindowModel(const QJsonObject &json)
{
    m_lineageName = json["lineageName"].toString(m_lineageName);
    m_l2lokiName = json["l2lokiName"].toString(m_l2lokiName);
}

QJsonObject WindowModel::toJson() const
{
    QJsonObject json;
    json.insert("lineageName", QJsonValue{m_lineageName});
    json.insert("l2lokiName", QJsonValue{m_l2lokiName});
    return json;
}

bool WindowModel::operator ==(const WindowModel &other) const
{
    return isEqualTo(other);
}

bool WindowModel::operator !=(const WindowModel &other) const
{
    return !isEqualTo(other);
}

const QString &WindowModel::getLineageName() const
{
    return m_lineageName;
}

const QString &WindowModel::getL2LokiName() const
{
    return m_l2lokiName;
}

void WindowModel::setLineageName(const QString &value)
{
    m_lineageName = value;
}

void WindowModel::setL2LokiName(const QString &value)
{
    m_l2lokiName = value;
}

bool WindowModel::isEqualTo(const WindowModel &other) const
{
    return      m_lineageName == other.m_lineageName
             && m_l2lokiName  == other.m_l2lokiName;
}
