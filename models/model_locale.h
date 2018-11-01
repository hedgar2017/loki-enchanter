#pragma once

#include "interfaces/i_jsonable.h"

#include <QString>
#include <QLocale>

class LocaleModel : public IJsonable
{

public:
    explicit LocaleModel() = default;
    explicit LocaleModel(const QJsonObject &);

    const QString           &getName() const;

    void                    setName(const QString &);

    QJsonObject             toJson() const override;
    bool                    operator ==(const LocaleModel &) const;
    bool                    operator !=(const LocaleModel &) const;

private:
    bool                    isEqualTo(const LocaleModel &) const;

    QString                 m_name {QLocale::system().name()};
};
