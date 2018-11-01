#include "model_relogin.h"

ReloginModel::ReloginModel(const QJsonObject &json)
{
    const QJsonObject &cancelPointJson = json["cancelPoint"].toObject();
    const QJsonObject &menuPointJson = json["menuPoint"].toObject();
    const QJsonObject &restartPointJson = json["restartPoint"].toObject();
    const QJsonObject &confirmPointJson = json["confirmPoint"].toObject();
    const QJsonObject &startPointJson = json["startPoint"].toObject();
    const QJsonObject &sitPointJson = json["sitPoint"].toObject();

    m_isEnabled = json["isEnabled"].toBool(m_isEnabled);
    m_reloginPeriod = json["reloginPeriod"].toInt(m_reloginPeriod);
    m_cancelPoint = QPoint{
            cancelPointJson["x"].toInt(m_cancelPoint.x()),
            cancelPointJson["y"].toInt(m_cancelPoint.y())
            };
    m_menuPoint = QPoint{
            menuPointJson["x"].toInt(m_menuPoint.x()),
            menuPointJson["y"].toInt(m_menuPoint.y())
            };
    m_restartPoint = QPoint{
            restartPointJson["x"].toInt(m_restartPoint.x()),
            restartPointJson["y"].toInt(m_restartPoint.y())
            };
    m_confirmPoint = QPoint{
            confirmPointJson["x"].toInt(m_confirmPoint.x()),
            confirmPointJson["y"].toInt(m_confirmPoint.y())
            };
    m_loggingOutDelay = json["loggingOutDelay"].toInt(m_loggingOutDelay);
    m_startPoint = QPoint{
            startPointJson["x"].toInt(m_startPoint.x()),
            startPointJson["y"].toInt(m_startPoint.y())
            };
    m_loggingInDelay = json["loggingInDelay"].toInt(m_loggingInDelay);
    m_sitPoint = QPoint{
            sitPointJson["x"].toInt(m_sitPoint.x()),
            sitPointJson["y"].toInt(m_sitPoint.y())
            };
    m_isMiddleClickEnabled = json["isMiddleClickEnabled"].toBool(m_isMiddleClickEnabled);
    m_isMiddleClickDouble = json["isMiddleClickDouble"].toBool(m_isMiddleClickDouble);
}

QJsonObject ReloginModel::toJson() const
{
    QJsonObject cancelPointJson;
    cancelPointJson.insert("x", QJsonValue{m_cancelPoint.x()});
    cancelPointJson.insert("y", QJsonValue{m_cancelPoint.y()});
    QJsonObject menuPointJson;
    menuPointJson.insert("x", QJsonValue{m_menuPoint.x()});
    menuPointJson.insert("y", QJsonValue{m_menuPoint.y()});
    QJsonObject restartPointJson;
    restartPointJson.insert("x", QJsonValue{m_restartPoint.x()});
    restartPointJson.insert("y", QJsonValue{m_restartPoint.y()});
    QJsonObject confirmPointJson;
    confirmPointJson.insert("x", QJsonValue{m_confirmPoint.x()});
    confirmPointJson.insert("y", QJsonValue{m_confirmPoint.y()});
    QJsonObject startPointJson;
    startPointJson.insert("x", QJsonValue{m_startPoint.x()});
    startPointJson.insert("y", QJsonValue{m_startPoint.y()});
    QJsonObject sitPointJson;
    sitPointJson.insert("x", QJsonValue{m_sitPoint.x()});
    sitPointJson.insert("y", QJsonValue{m_sitPoint.y()});

    QJsonObject json;
    json.insert("isEnabled", QJsonValue{m_isEnabled});
    json.insert("reloginPeriod", QJsonValue{m_reloginPeriod});
    json.insert("cancelPoint", QJsonValue{cancelPointJson});
    json.insert("menuPoint", QJsonValue{menuPointJson});
    json.insert("restartPoint", QJsonValue{restartPointJson});
    json.insert("confirmPoint", QJsonValue{confirmPointJson});
    json.insert("loggingOutDelay", QJsonValue{m_loggingOutDelay});
    json.insert("startPoint", QJsonValue{startPointJson});
    json.insert("loggingInDelay", QJsonValue{m_loggingInDelay});
    json.insert("sitPoint", QJsonValue{sitPointJson});
    json.insert("isMiddleClickEnabled", QJsonValue{m_isMiddleClickEnabled});
    json.insert("isMiddleClickDouble", QJsonValue{m_isMiddleClickDouble});
    return json;
}

bool ReloginModel::operator ==(const ReloginModel &other) const
{
    return isEqualTo(other);
}

bool ReloginModel::operator !=(const ReloginModel &other) const
{
    return !isEqualTo(other);
}

bool ReloginModel::isEnabled() const
{
    return m_isEnabled;
}

int ReloginModel::getReloginPeriod() const
{
    return m_reloginPeriod;
}

const QPoint &ReloginModel::getCancelPoint() const
{
    return m_cancelPoint;
}

const QPoint &ReloginModel::getMenuPoint() const
{
    return m_menuPoint;
}

const QPoint &ReloginModel::getRestartPoint() const
{
    return m_restartPoint;
}

const QPoint &ReloginModel::getConfirmPoint() const
{
    return m_confirmPoint;
}

int ReloginModel::getLoggingOutDelay() const
{
    return m_loggingOutDelay;
}

const QPoint &ReloginModel::getStartPoint() const
{
    return m_startPoint;
}

int ReloginModel::getLoggingInDelay() const
{
    return m_loggingInDelay;
}

const QPoint &ReloginModel::getSitPoint() const
{
    return m_sitPoint;
}

bool ReloginModel::isMiddleClickEnabled() const
{
    return m_isMiddleClickEnabled;
}

bool ReloginModel::isMiddleClickDouble() const
{
    return m_isMiddleClickDouble;
}

void ReloginModel::setEnabled(const bool value)
{
    m_isEnabled = value;
}

void ReloginModel::setReloginPeriod(const int value)
{
    m_reloginPeriod = value;
}

void ReloginModel::setCancelPoint(const QPoint &value)
{
    m_cancelPoint = value;
}

void ReloginModel::setMenuPoint(const QPoint &value)
{
    m_menuPoint = value;
}

void ReloginModel::setRestartPoint(const QPoint &value)
{
    m_restartPoint = value;
}

void ReloginModel::setConfirmPoint(const QPoint &value)
{
    m_confirmPoint = value;
}

void ReloginModel::setLoggingOutDelay(const int value)
{
    m_loggingOutDelay = value;
}

void ReloginModel::setStartPoint(const QPoint &value)
{
    m_startPoint = value;
}

void ReloginModel::setLoggingInDelay(const int value)
{
    m_loggingInDelay = value;
}

void ReloginModel::setSitPoint(const QPoint &value)
{
    m_sitPoint = value;
}

void ReloginModel::setMiddleClickEnabled(const bool value)
{
    m_isMiddleClickEnabled = value;
}

void ReloginModel::setMiddleClickDouble(const bool value)
{
    m_isMiddleClickDouble = value;
}

bool ReloginModel::isEqualTo(const ReloginModel &other) const
{
    return    m_isEnabled               == other.m_isEnabled
           && m_reloginPeriod           == other.m_reloginPeriod
           && m_cancelPoint             == other.m_cancelPoint
           && m_menuPoint               == other.m_menuPoint
           && m_restartPoint            == other.m_restartPoint
           && m_confirmPoint            == other.m_confirmPoint
           && m_loggingOutDelay         == other.m_loggingOutDelay
           && m_startPoint              == other.m_startPoint
           && m_loggingInDelay          == other.m_loggingInDelay
           && m_sitPoint                == other.m_sitPoint
           && m_isMiddleClickEnabled    == other.m_isMiddleClickEnabled
           && m_isMiddleClickDouble     == other.m_isMiddleClickDouble;
}
