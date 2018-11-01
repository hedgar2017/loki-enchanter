#pragma once

#include "interfaces/i_jsonable.h"

#include <QStringList>

class EnchantModel : public IJsonable
{

public:
    explicit EnchantModel() = default;
    explicit EnchantModel(const QJsonObject &);

    int                         getItemAmount() const;
    int                         getSkipItems() const;
    int                         getItemLevel() const;
    int                         getScrollCooldown() const;
    int                         getDelayBeforeStart() const;
    const QStringList           &getItemSignatureList() const;
    bool                        isGlobalStopHookEnabled() const;

    bool                        isSignaturePresent(const QString &) const;

    void                        setItemAmount(const int);
    void                        setSkipItems(const int);
    void                        setItemLevel(const int);
    void                        setScrollCooldown(const int);
    void                        setDelayBeforeStart(const int);
    void                        setItemSignatureList(const QStringList &);
    void                        setGlobalStopHookEnabled(const bool);

    QJsonObject                 toJson() const override;
    bool                        operator ==(const EnchantModel &) const;
    bool                        operator !=(const EnchantModel &) const;

private:
    bool                        isEqualTo(const EnchantModel &) const;

    int                         m_itemAmount                {6};
    int                         m_skipItems                 {0};
    int                         m_itemLevel                 {15};
    int                         m_scrollCooldown            {1050};
    int                         m_delayBeforeStart          {3000};
    bool                        m_isGlobalStopHookEnabled   {false};
    QStringList                 m_itemSignatureList;
};
