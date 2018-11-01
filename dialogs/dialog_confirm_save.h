#pragma once

#include <QMessageBox>

class SaveConfirmDialog : public QMessageBox
{
    Q_OBJECT

public:
    enum Status {
        YES = 1,
        NO = 0,
        CANCEL = -1
    };

    explicit SaveConfirmDialog(QWidget *parent = nullptr);
    SaveConfirmDialog(const SaveConfirmDialog &) = delete;
    void operator =(const SaveConfirmDialog &) = delete;
    virtual ~SaveConfirmDialog() override = default;

    int         exec() override;

protected:
    void        accept() override;
    void        reject() override;
    void        closeEvent(QCloseEvent *) override;

private:
    int         m_status {Status::CANCEL};
};
