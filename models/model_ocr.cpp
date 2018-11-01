#include "model_ocr.h"

OCRModel::OCRModel(const QJsonObject &json)
{
    QJsonObject coordinatesJson = json["coordinates"].toObject();
    m_screenshotRectangle = QRect(
            coordinatesJson["x"].toInt(m_screenshotRectangle.x()),
            coordinatesJson["y"].toInt(m_screenshotRectangle.y()),
            coordinatesJson["w"].toInt(m_screenshotRectangle.width()),
            coordinatesJson["h"].toInt(m_screenshotRectangle.height())
            );
}

QJsonObject OCRModel::toJson() const
{
    QJsonObject coordinatesJson;
    coordinatesJson.insert("x", QJsonValue{m_screenshotRectangle.x()});
    coordinatesJson.insert("y", QJsonValue{m_screenshotRectangle.y()});
    coordinatesJson.insert("w", QJsonValue{m_screenshotRectangle.width()});
    coordinatesJson.insert("h", QJsonValue{m_screenshotRectangle.height()});

    QJsonObject json;
    json.insert("coordinates", QJsonValue{coordinatesJson});
    return json;
}

bool OCRModel::operator ==(const OCRModel &other) const
{
    return isEqualTo(other);
}

bool OCRModel::operator !=(const OCRModel &other) const
{
    return !isEqualTo(other);
}

const QRect &OCRModel::getScreenshotRectangle() const
{
    return m_screenshotRectangle;
}

void OCRModel::setScreenshotRectangle(const QRect &rect)
{
    m_screenshotRectangle = rect;
}

bool OCRModel::isEqualTo(const OCRModel &other) const
{
    return m_screenshotRectangle == other.m_screenshotRectangle;
}
