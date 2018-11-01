#include "model_enchant.h"

#include <QJsonArray>

EnchantModel::EnchantModel(const QJsonObject &json)
{
    m_itemAmount = json["itemAmount"].toInt(m_itemAmount);
    m_skipItems = json["skipItems"].toInt(m_skipItems);
    m_itemLevel = json["itemLevel"].toInt(m_itemLevel);
    m_scrollCooldown = json["scrollCooldown"].toInt(m_scrollCooldown);
    m_delayBeforeStart = json["delayBeforeStart"].toInt(m_delayBeforeStart);
    m_isGlobalStopHookEnabled = json["isGlobalStopHookEnabled"].toBool(m_isGlobalStopHookEnabled);
    foreach (const QJsonValue &v, json["itemSignatureList"].toArray()) {
        QString s = v.toString();
        if (!s.isEmpty()) {
            m_itemSignatureList.append(v.toString());
        }
    }
}

QJsonObject EnchantModel::toJson() const
{
    QJsonObject json;
    json.insert("itemAmount", QJsonValue{m_itemAmount});
    json.insert("skipItems", QJsonValue{m_skipItems});
    json.insert("itemLevel", QJsonValue{m_itemLevel});
    json.insert("delayBeforeStart", QJsonValue{m_delayBeforeStart});
    json.insert("scrollCooldown", QJsonValue{m_scrollCooldown});
    json.insert("isGlobalStopHookEnabled", QJsonValue{m_isGlobalStopHookEnabled});
    json.insert("itemSignatureList", QJsonArray::fromStringList(m_itemSignatureList));
    return json;
}

bool EnchantModel::operator ==(const EnchantModel &other) const
{
    return isEqualTo(other);
}

bool EnchantModel::operator !=(const EnchantModel &other) const
{
    return !isEqualTo(other);
}

int EnchantModel::getItemAmount() const
{
    return m_itemAmount;
}

int EnchantModel::getSkipItems() const
{
    return m_skipItems;
}

int EnchantModel::getItemLevel() const
{
    return m_itemLevel;
}

int EnchantModel::getScrollCooldown() const
{
    return m_scrollCooldown;
}

int EnchantModel::getDelayBeforeStart() const
{
    return m_delayBeforeStart;
}

const QStringList &EnchantModel::getItemSignatureList() const
{
    return m_itemSignatureList;
}

bool EnchantModel::isGlobalStopHookEnabled() const
{
    return m_isGlobalStopHookEnabled;
}

bool EnchantModel::isSignaturePresent(const QString &signature) const
{
    foreach (const QString &s, m_itemSignatureList) {
        if (signature.contains(s)) {
            return true;
        }
    }
    return false;
}

void EnchantModel::setItemAmount(const int value)
{
    m_itemAmount = value;
}

void EnchantModel::setSkipItems(const int value)
{
    m_skipItems = value;
}

void EnchantModel::setItemLevel(const int value)
{
    m_itemLevel = value;
}

void EnchantModel::setScrollCooldown(const int value)
{
    m_scrollCooldown = value;
}

void EnchantModel::setDelayBeforeStart(const int value)
{
    m_delayBeforeStart = value;
}

void EnchantModel::setItemSignatureList(const QStringList &value)
{
    m_itemSignatureList = value;
}

void EnchantModel::setGlobalStopHookEnabled(const bool value)
{
    m_isGlobalStopHookEnabled = value;
}

bool EnchantModel::isEqualTo(const EnchantModel &other) const
{
    return    m_itemAmount                  == other.m_itemAmount
           && m_skipItems                   == other.m_skipItems
           && m_itemLevel                   == other.m_itemLevel
           && m_delayBeforeStart            == other.m_delayBeforeStart
           && m_scrollCooldown              == other.m_scrollCooldown
           && m_itemSignatureList           == other.m_itemSignatureList
           && m_isGlobalStopHookEnabled     == other.m_isGlobalStopHookEnabled;
}
