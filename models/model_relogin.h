#pragma once

#include "interfaces/i_jsonable.h"

#include <QPoint>

class ReloginModel : public IJsonable
{

public:
    explicit ReloginModel() = default;
    explicit ReloginModel(const QJsonObject &);

    QJsonObject					toJson() const override;
    bool                        operator ==(const ReloginModel &) const;
    bool                        operator !=(const ReloginModel &) const;

    bool                        isEnabled() const;
    int                         getReloginPeriod() const;
    const QPoint                &getCancelPoint() const;
    const QPoint                &getMenuPoint() const;
    const QPoint                &getRestartPoint() const;
    const QPoint                &getConfirmPoint() const;
    int                         getLoggingOutDelay() const;
    const QPoint                &getStartPoint() const;
    int                         getLoggingInDelay() const;
    const QPoint                &getSitPoint() const;
    bool                        isMiddleClickEnabled() const;
    bool                        isMiddleClickDouble() const;

    void                        setEnabled(const bool);
    void                        setReloginPeriod(const int);
    void                        setCancelPoint(const QPoint &);
    void                        setMenuPoint(const QPoint &);
    void                        setRestartPoint(const QPoint &);
    void                        setConfirmPoint(const QPoint &);
    void                        setLoggingOutDelay(const int);
    void                        setStartPoint(const QPoint &);
    void                        setLoggingInDelay(const int);
    void                        setSitPoint(const QPoint &);
    void                        setMiddleClickEnabled(const bool);
    void                        setMiddleClickDouble(const bool);

private:
    bool                        isEqualTo(const ReloginModel &) const;

    bool                        m_isEnabled                 {false};
    int                         m_reloginPeriod             {60};
    QPoint						m_cancelPoint               {QPoint{398, 608}};
    QPoint						m_menuPoint                 {QPoint{398, 608}};
    QPoint						m_restartPoint              {QPoint{398, 608}};
    QPoint                      m_confirmPoint              {QPoint{398, 608}};
    int                         m_loggingOutDelay           {15000};
    QPoint                      m_startPoint                {QPoint{398, 608}};
    int                         m_loggingInDelay            {30000};
    QPoint                      m_sitPoint                  {QPoint{398, 608}};
    bool                        m_isMiddleClickEnabled      {false};
    bool                        m_isMiddleClickDouble       {false};
};
