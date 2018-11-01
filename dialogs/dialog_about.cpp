#include "dialog_about.h"

#include <QGridLayout>
#include <QIcon>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog{parent}

    , mw_nameLabel{new QLabel{APP_NAME, this}}
    , mw_versionLabel{new QLabel{APP_VERSION, this}}
{
    QPalette textPalette;
    textPalette.setColor(mw_nameLabel->foregroundRole(), Qt::yellow);

    QPixmap background(":/about");
    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Background, background);
    setPalette(backgroundPalette);

    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setWindowIcon(QIcon{":/icons/about"});
    setWindowTitle(tr("WINDOW_TITLE"));
    adjustSize();
    setFixedSize(background.size());

    QFont font = mw_nameLabel->font();
    font.setPointSize(FONT_SIZE);

    mw_nameLabel->setPalette(textPalette);
    mw_nameLabel->setFont(font);
    mw_nameLabel->setGeometry(
                FONT_SIZE,
                FONT_SIZE / 2,
                mw_versionLabel->geometry().width(),
                mw_versionLabel->geometry().height()
                );

    mw_versionLabel->setPalette(textPalette);
    mw_versionLabel->setFont(font);
    mw_versionLabel->setGeometry(
                background.width() - mw_versionLabel->fontMetrics().width(APP_VERSION) - FONT_SIZE,
                FONT_SIZE / 2,
                mw_versionLabel->geometry().width(),
                mw_versionLabel->geometry().height()
                );
}
