#include "model_locale.h"

LocaleModel::LocaleModel(const QJsonObject &json)
{
    m_name = json["name"].toString(m_name);
}

QJsonObject LocaleModel::toJson() const
{
    QJsonObject json;
    json.insert("name", QJsonValue{m_name});
    return json;
}

bool LocaleModel::operator ==(const LocaleModel &other) const
{
    return isEqualTo(other);
}

bool LocaleModel::operator !=(const LocaleModel &other) const
{
    return !isEqualTo(other);
}

const QString &LocaleModel::getName() const
{
    return m_name;
}

void LocaleModel::setName(const QString &value)
{
    m_name = value;
}

bool LocaleModel::isEqualTo(const LocaleModel &other) const
{
    return m_name == other.m_name;
}
