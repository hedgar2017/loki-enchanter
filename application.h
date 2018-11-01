#pragma once

#include "interfaces/i_jsonable.h"

#include <QLocale>

#include "models/model_enchant.h"
#include "models/model_ocr.h"
#include "models/model_macro.h"
#include "models/model_relogin.h"
#include "models/model_window.h"
#include "models/model_locale.h"

class Application : public IJsonable
{

public:
    explicit Application() = default;
    explicit Application(const QJsonObject &);
    virtual ~Application() = default;

    QJsonObject             toJson() const override;

    bool                    operator ==(const Application &) const;
    bool                    operator !=(const Application &) const;

    static Application      *loadFromFile(const QString &);
    void                    saveToFile(const QString &);

    EnchantModel            &getEnchantModel();
    const EnchantModel      &getEnchantModel() const;
    OCRModel                &getOcrModel();
    const OCRModel          &getOcrModel() const;
    MacroModel              &getMacroModel();
    const MacroModel        &getMacroModel() const;
    ReloginModel            &getReloginModel();
    const ReloginModel      &getReloginModel() const;
    WindowModel             &getWindowModel();
    const WindowModel       &getWindowModel() const;
    LocaleModel             &getLocaleModel();
    const LocaleModel       &getLocaleModel() const;

    const QString           &getProfileName() const;

    void                    setProfileName(const QString &);

private:
    bool                    isEqualTo(const Application &) const;

    EnchantModel            m_enchantModel;
    OCRModel                m_ocrModel;
    MacroModel              m_macroModel;
    ReloginModel            m_reloginModel;
    WindowModel             m_windowModel;
    LocaleModel             m_localeModel;

    QString                 m_profileName;
};
