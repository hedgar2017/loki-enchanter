#include "ocr/ocr.h"

#include <stdexcept>

#include "services/service_storage.h"

OCR::~OCR()
{
    m_tess.End();
}

void OCR::initialize()
{
    if (0 != m_tess.Init(StorageService::pathTessdata().toUtf8().constData(), "eng")) {
        throw std::runtime_error{"ERROR_TESSERACT_INITIALIZATION"};
    }
}

QString OCR::recognize(const QImage &image)
{
    m_tess.SetImage(image.bits(), image.width(), image.height(), BYTES_PER_PIXEL, BYTES_PER_PIXEL * image.width());
    m_tess.Recognize(nullptr);
    QString result{m_tess.GetUTF8Text()};
    m_tess.Clear();
    return result;
}

tesseract::TessBaseAPI &OCR::getTess()
{
    return m_tess;
}
