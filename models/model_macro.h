#pragma once

#include "interfaces/i_jsonable.h"

#include <QPoint>

class MacroModel : public IJsonable
{

public:
    explicit MacroModel() = default;
    explicit MacroModel(const QJsonObject &);

	const QPoint				&getScrollPoint() const;
    int                         getScrollPointDelay() const;
    const QPoint				&getItemPoint() const;
    int                         getItemPointDelay() const;
    const QPoint				&getConfirmPoint() const;

    void						setScrollPoint(const QPoint &);
    void                        setScrollPointDelay(const int);
    void						setItemPoint(const QPoint &);
    void                        setItemPointDelay(const int);
    void						setConfirmPoint(const QPoint &);

    QJsonObject					toJson() const override;
    bool                        operator ==(const MacroModel &) const;
    bool                        operator !=(const MacroModel &) const;

private:
    bool                        isEqualTo(const MacroModel &) const;

    QPoint						m_scrollPoint           {QPoint{398, 608}};
    int                         m_scrollPointDelay      {250};
    QPoint						m_itemPoint             {QPoint{375, 245}};
    int                         m_itemPointDelay        {250};
    QPoint						m_confirmPoint          {QPoint{440, 566}};
};
