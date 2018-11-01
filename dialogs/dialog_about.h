#pragma once

#include <QDialog>

#include <QString>
#include <QLabel>

#define APP_NAME        "L2Loki"
#define APP_VERSION     "v1.0.0"

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    AboutDialog(const AboutDialog &) = delete;
    void operator =(const AboutDialog &) = delete;
    virtual ~AboutDialog() override = default;

private:
    QLabel                  *mw_nameLabel;
    QLabel                  *mw_versionLabel;

    static const int        FONT_SIZE {12};
};
