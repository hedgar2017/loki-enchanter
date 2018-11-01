#include "model_macro.h"

MacroModel::MacroModel(const QJsonObject &json)
{
    const QJsonObject &scrollPointJson = json["scrollPoint"].toObject();
    const QJsonObject &itemPointJson = json["itemPoint"].toObject();
    const QJsonObject &confirmPointJson = json["confirmPoint"].toObject();

    m_scrollPoint = QPoint{
            scrollPointJson["x"].toInt(m_scrollPoint.x()),
            scrollPointJson["y"].toInt(m_scrollPoint.y())
            };
    m_scrollPointDelay = json["scrollPointDelay"].toInt(m_scrollPointDelay);
    m_itemPoint = QPoint{
            itemPointJson["x"].toInt(m_itemPoint.x()),
            itemPointJson["y"].toInt(m_itemPoint.y())
            };
    m_itemPointDelay = json["itemPointDelay"].toInt(m_itemPointDelay);
    m_confirmPoint = QPoint{
            confirmPointJson["x"].toInt(m_confirmPoint.x()),
            confirmPointJson["y"].toInt(m_confirmPoint.y())
            };
}

QJsonObject MacroModel::toJson() const
{
    QJsonObject scrollPointJson;
    scrollPointJson.insert("x", QJsonValue{m_scrollPoint.x()});
    scrollPointJson.insert("y", QJsonValue{m_scrollPoint.y()});
    QJsonObject itemPointJson;
    itemPointJson.insert("x", QJsonValue{m_itemPoint.x()});
    itemPointJson.insert("y", QJsonValue{m_itemPoint.y()});
    QJsonObject confirmPointJson;
    confirmPointJson.insert("x", QJsonValue{m_confirmPoint.x()});
    confirmPointJson.insert("y", QJsonValue{m_confirmPoint.y()});

    QJsonObject json;
    json.insert("scrollPoint", QJsonValue{scrollPointJson});
    json.insert("scrollPointDelay", QJsonValue{m_scrollPointDelay});
    json.insert("itemPoint", QJsonValue{itemPointJson});
    json.insert("itemPointDelay", QJsonValue{m_itemPointDelay});
    json.insert("confirmPoint", QJsonValue{confirmPointJson});
    return json;
}

bool MacroModel::operator ==(const MacroModel &other) const
{
    return isEqualTo(other);
}

bool MacroModel::operator !=(const MacroModel &other) const
{
    return !isEqualTo(other);
}

const QPoint &MacroModel::getScrollPoint() const
{
    return m_scrollPoint;
}

int MacroModel::getScrollPointDelay() const
{
    return m_scrollPointDelay;
}

const QPoint &MacroModel::getItemPoint() const
{
    return m_itemPoint;
}

int MacroModel::getItemPointDelay() const
{
    return m_itemPointDelay;
}

const QPoint &MacroModel::getConfirmPoint() const
{
    return m_confirmPoint;
}

void MacroModel::setScrollPoint(const QPoint &point)
{
    m_scrollPoint = point;
}

void MacroModel::setScrollPointDelay(const int value)
{
    m_scrollPointDelay = value;
}

void MacroModel::setItemPoint(const QPoint &point)
{
    m_itemPoint = point;
}

void MacroModel::setItemPointDelay(const int value)
{
    m_itemPointDelay = value;
}

void MacroModel::setConfirmPoint(const QPoint &point)
{
    m_confirmPoint = point;
}

bool MacroModel::isEqualTo(const MacroModel &other) const
{
    return    m_scrollPoint         == other.m_scrollPoint
           && m_scrollPointDelay    == other.m_scrollPointDelay
           && m_itemPoint           == other.m_itemPoint
           && m_itemPointDelay      == other.m_itemPointDelay
           && m_confirmPoint        == other.m_confirmPoint;
}
