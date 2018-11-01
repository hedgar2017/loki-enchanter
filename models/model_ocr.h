#pragma once

#include "interfaces/i_jsonable.h"

#include <QRect>

class OCRModel : public IJsonable
{

public:
    explicit OCRModel() = default;
    explicit OCRModel(const QJsonObject &);

    const QRect&            getScreenshotRectangle() const;

    void                    setScreenshotRectangle(const QRect &);

    QJsonObject             toJson() const override;
    bool                    operator ==(const OCRModel &) const;
    bool                    operator !=(const OCRModel &) const;

private:
    bool                    isEqualTo(const OCRModel &) const;

    QRect                   m_screenshotRectangle {QRect{362, 214, 22, 12}};
};
