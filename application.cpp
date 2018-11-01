#include "application.h"

#include <QFile>
#include <QJsonParseError>

Application::Application(const QJsonObject &json) {
    m_enchantModel          = EnchantModel{json["Enchant"].toObject()};
    m_ocrModel              = OCRModel{json["OCR"].toObject()};
    m_macroModel            = MacroModel{json["Macro"].toObject()};
    m_reloginModel          = ReloginModel{json["Relogin"].toObject()};
    m_windowModel           = WindowModel{json["Window"].toObject()};
    m_localeModel           = LocaleModel{json["Locale"].toObject()};

    m_profileName           = json["ProfileName"].toString(m_profileName);
}

QJsonObject Application::toJson() const
{
    QJsonObject json;
    json.insert("Enchant", m_enchantModel.toJson());
    json.insert("OCR", m_ocrModel.toJson());
    json.insert("Macro", m_macroModel.toJson());
    json.insert("Relogin", m_reloginModel.toJson());
    json.insert("Window", m_windowModel.toJson());
    json.insert("Locale", m_localeModel.toJson());

    json.insert("ProfileName", QJsonValue{m_profileName});
    return json;
}

bool Application::operator ==(const Application &other) const
{
    return isEqualTo(other);
}

bool Application::operator !=(const Application &other) const
{
    return !isEqualTo(other);
}

Application *Application::loadFromFile(const QString &path)
{
    QFile configFile{path};
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error{"ERROR_FILE_OPENING"};
    }

    QString configJsonString = configFile.readAll();
    configFile.close();

    QJsonParseError jsonParseError;
    QJsonObject json = QJsonDocument::fromJson(configJsonString.toUtf8(), &jsonParseError).object();
    if (QJsonParseError::NoError != jsonParseError.error) {
        throw std::runtime_error{"ERROR_FILE_PARSING"};
    }

    return new Application{json};
}

void Application::saveToFile(const QString &path)
{
    QFile configFile{path};
    if (!configFile.open(QFile::WriteOnly)) {
        throw std::runtime_error{"ERROR_FILE_OPENING"};
    }
    setProfileName(path.split("/").back());
    configFile.write(QJsonDocument{toJson()}.toJson());
}

EnchantModel &Application::getEnchantModel()
{
    return m_enchantModel;
}

const EnchantModel &Application::getEnchantModel() const
{
    return m_enchantModel;
}

OCRModel &Application::getOcrModel()
{
    return m_ocrModel;
}

const OCRModel &Application::getOcrModel() const
{
    return m_ocrModel;
}

MacroModel &Application::getMacroModel()
{
    return m_macroModel;
}

const MacroModel &Application::getMacroModel() const
{
    return m_macroModel;
}

ReloginModel &Application::getReloginModel()
{
    return m_reloginModel;
}

const ReloginModel &Application::getReloginModel() const
{
    return m_reloginModel;
}

WindowModel &Application::getWindowModel()
{
    return m_windowModel;
}

const WindowModel &Application::getWindowModel() const
{
    return m_windowModel;
}

LocaleModel &Application::getLocaleModel()
{
    return m_localeModel;
}

const LocaleModel &Application::getLocaleModel() const
{
    return m_localeModel;
}

const QString &Application::getProfileName() const
{
    return m_profileName;
}

void Application::setProfileName(const QString &value)
{
    m_profileName = value;
}

bool Application::isEqualTo(const Application &other) const
{
    return    m_enchantModel    == other.m_enchantModel
           && m_ocrModel        == other.m_ocrModel
           && m_macroModel      == other.m_macroModel
           && m_reloginModel    == other.m_reloginModel
           && m_windowModel     == other.m_windowModel
           && m_localeModel     == other.m_localeModel
           && m_profileName     == other.m_profileName;
}
