#pragma once

#include "interfaces/i_jsonable.h"

#include <QString>

class WindowModel : public IJsonable
{

public:
    explicit WindowModel() = default;
    explicit WindowModel(const QJsonObject &);

    const QString           &getLineageName() const;
    const QString           &getL2LokiName() const;

    void                    setLineageName(const QString &);
    void                    setL2LokiName(const QString &);

    QJsonObject             toJson() const override;
    bool                    operator ==(const WindowModel &) const;
    bool                    operator !=(const WindowModel &) const;

private:
    bool                    isEqualTo(const WindowModel &) const;

    QString                 m_lineageName   {"Lineage II"};
    QString                 m_l2lokiName    {"L2Loki"};
};
