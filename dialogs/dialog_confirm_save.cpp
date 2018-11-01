#include "dialog_confirm_save.h"

#include <QPushButton>

SaveConfirmDialog::SaveConfirmDialog(QWidget *parent)
    : QMessageBox{parent}
{
    setWindowIcon(QIcon{":/icons/save"});
    setIconPixmap(QIcon{":/icons/save"}.pixmap(QSize{32, 32}));
    setWindowTitle(tr("WINDOW_TITLE"));
    setText(tr("TEXT"));

    QPushButton *yesButton = addButton(tr("PUSH_BUTTON_YES_TEXT"), QMessageBox::YesRole);
    connect(yesButton, &QPushButton::clicked, this, &SaveConfirmDialog::accept);

    QPushButton *noButton = addButton(tr("PUSH_BUTTON_NO_TEXT"), QMessageBox::NoRole);
    connect(noButton, &QPushButton::clicked, this, &SaveConfirmDialog::reject);
}

int SaveConfirmDialog::exec()
{
    QMessageBox::exec();
    return m_status;
}

void SaveConfirmDialog::accept()
{
    QMessageBox::accept();
    m_status = Status::YES;
}

void SaveConfirmDialog::reject()
{
    QMessageBox::reject();
    m_status = Status::NO;
}

void SaveConfirmDialog::closeEvent(QCloseEvent *event)
{
    QMessageBox::closeEvent(event);
    m_status = Status::CANCEL;
}
