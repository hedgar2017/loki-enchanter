#pragma once

#include <QString>
#include <QImage>

#pragma warning(push, 0)
#include "tesseract/baseapi.h"
#pragma warning(pop)

class OCR
{

public:
    explicit OCR() = default;
    OCR(const OCR &) = delete;
    void operator =(const OCR &) = delete;
    virtual ~OCR();

    virtual void            initialize();
    virtual QString         recognize(const QImage &);

protected:
    tesseract::TessBaseAPI  &getTess();

private:
    tesseract::TessBaseAPI  m_tess;

    static const int        BYTES_PER_PIXEL     {4};
};
