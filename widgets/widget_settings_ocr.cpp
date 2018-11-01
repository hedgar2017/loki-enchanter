#include "widget_settings_ocr.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>

#include <stdexcept>

#include "dialogs/dialog_input_screen_rect.h"
#include "widgets/widget_group_box_wrapper.h"
#include "ocr/ocr_processed.h"
#include "screenshot/screenshot.h"

OCRSettingsWidget::OCRSettingsWidget(OCRModel &model, QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_rectangleInput{new QRectInputWidget{this}}
    , mw_rectangleGraphicsView{new QGraphicsView{this}}
    , mw_recognizedTextEdit{new QTextEdit{this}}

    , mw_testPushButton{new QPushButton{this}}
    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_rectangleInput),             0, 0, 1, 2);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_rectangleGraphicsView),      1, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_recognizedTextEdit),         1, 1);
    layout->addWidget(mw_testPushButton,                                    2, 0, 1, 2);
    layout->addWidget(mw_resetPushButton,                                   3, 0, 1, 2);

    GET_GROUP_BOX_WRAPPER(mw_rectangleInput)->setTitle(tr("INPUT_RECTANGLE_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_rectangleGraphicsView)->setTitle(tr("GRAPHICS_VIEW_RECTANGLE_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_recognizedTextEdit)->setTitle(tr("TEXT_EDIT_RECOGNIZED_TITLE"));
    mw_testPushButton->setText(tr("PUSH_BUTTON_TEST_TEXT"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    mw_recognizedTextEdit->setReadOnly(true);

    setLayout(layout);
    setFixedHeight(400);
    reset();

    connect(mw_testPushButton, &QPushButton::clicked, this, &OCRSettingsWidget::test);
    connect(mw_resetPushButton, &QPushButton::clicked, this, &OCRSettingsWidget::reset);
}

void OCRSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    mr_model.setScreenshotRectangle(mw_rectangleInput->get());
}

bool OCRSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    if (!mw_rectangleInput->isValid(error)) {
        errorList << tr("ERROR_RECTANGLE_INVALID");
        isValid = false;
    }
    error += errorList.join("\r\n");
    return isValid;
}

void OCRSettingsWidget::reset() {
    mw_rectangleInput->set(mr_model.getScreenshotRectangle());
}

void OCRSettingsWidget::test() {
    QString error;
    if (!isValid(error)) {
        QMessageBox::critical(this, tr("ERROR"), error, QMessageBox::Ok);
        return;
    }

    ProcessedOCR ocr;
    ocr.initialize();

    QPixmap screenshot = Screenshot::make(mw_rectangleInput->get());
    QImage image = ProcessedOCR::pixmapToProcessedImage(screenshot);
    if (nullptr != mw_rectangleGraphicsView->scene()) {
        delete mw_rectangleGraphicsView->scene();
    }
    mw_rectangleGraphicsView->setScene(new QGraphicsScene());
    mw_rectangleGraphicsView->scene()->addPixmap(QPixmap::fromImage(image));

    QString tesseractOutput = ocr.recognize(image);
    QStringList recognizedWords = tesseractOutput.split(QRegExp{"[\r\n]"}, QString::SkipEmptyParts);
    mw_recognizedTextEdit->setText(recognizedWords.join("\r\n"));
}
