#pragma once

#include "ocr.h"

#include <QPixmap>

class ProcessedOCR : public OCR
{

public:
    explicit ProcessedOCR() = default;
    ProcessedOCR(const ProcessedOCR &) = delete;
    void operator =(const ProcessedOCR &) = delete;
    virtual ~ProcessedOCR() override = default;

    virtual QString         recognize(const QImage &) override;

    static QImage           pixmapToProcessedImage(const QPixmap &, int scaleFactor = SCALE_FACTOR);

private:
    static const int        SCALE_FACTOR        {2};
};
