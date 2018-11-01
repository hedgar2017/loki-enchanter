#include "ocr_processed.h"

QString ProcessedOCR::recognize(const QImage &image)
{
    return OCR::recognize(image).replace('?', '7');
}

QImage ProcessedOCR::pixmapToProcessedImage(const QPixmap &pixmap, int scaleFactor)
{
    static QColor colorToReplace{176, 153, 121};
    QImage image = (scaleFactor == 1 ? pixmap : pixmap.scaled(pixmap.size() * scaleFactor)).toImage();
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            if (image.pixelColor(i, j) == colorToReplace) {
                image.setPixelColor(i, j, QColor(Qt::white));
            }
        }
    }
    return image;
}
