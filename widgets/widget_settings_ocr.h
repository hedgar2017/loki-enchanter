#pragma once

#include <QWidget>
#include "interfaces/i_applyable.h"
#include "interfaces/i_validable.h"

#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>

#include "widget_input_qrect.h"
#include "models/model_ocr.h"

class OCRSettingsWidget : public QWidget, public IApplyable, public IValidable
{
    Q_OBJECT

public:
    explicit OCRSettingsWidget(OCRModel &, QWidget *parent = nullptr);
    OCRSettingsWidget(const OCRSettingsWidget &) = delete;
    void operator =(const OCRSettingsWidget &) = delete;
    virtual ~OCRSettingsWidget() = default;

    void                            apply() override;
    bool                            isValid(QString &error) const override;

private slots:
    void                            reset();
    void                            test();

private:
    OCRModel                        &mr_model;

    QRectInputWidget                *mw_rectangleInput;
    QGraphicsView                   *mw_rectangleGraphicsView;
    QTextEdit                       *mw_recognizedTextEdit;
    QPushButton                     *mw_testPushButton;

    QPushButton                     *mw_resetPushButton;

    static const int                SCREENSHOT_SCALE_FACTOR {2};
};
