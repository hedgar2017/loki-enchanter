#include "dialog_confirm_reboot.h"

#include <QPushButton>

RebootConfirmDialog::RebootConfirmDialog(QWidget *parent)
    : QMessageBox{parent}
{
    setWindowTitle(tr("WINDOW_TITLE"));
    setText(tr("TEXT"));

    QPushButton *yesButton = addButton(tr("PUSH_BUTTON_YES_TEXT"), QMessageBox::YesRole);
    connect(yesButton, &QPushButton::clicked, this, &RebootConfirmDialog::accept);

    QPushButton *noButton = addButton(tr("PUSH_BUTTON_NO_TEXT"), QMessageBox::NoRole);
    connect(noButton, &QPushButton::clicked, this, &RebootConfirmDialog::reject);
}

int RebootConfirmDialog::exec()
{
    QMessageBox::exec();
    return m_status;
}

void RebootConfirmDialog::accept()
{
    QMessageBox::accept();
    m_status = Status::YES;
}

void RebootConfirmDialog::reject()
{
    QMessageBox::reject();
    m_status = Status::NO;
}

void RebootConfirmDialog::closeEvent(QCloseEvent *event)
{
    QMessageBox::closeEvent(event);
    m_status = Status::NO;
}
