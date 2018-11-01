#pragma once

#include <QMessageBox>

class RebootConfirmDialog : public QMessageBox
{
    Q_OBJECT

public:
    enum Status {
        YES = 1,
        NO = 0
    };

    explicit RebootConfirmDialog(QWidget *parent = nullptr);
    RebootConfirmDialog(const RebootConfirmDialog &) = delete;
    void operator =(const RebootConfirmDialog &) = delete;
    virtual ~RebootConfirmDialog() override = default;

    int         exec() override;

protected:
    void        accept() override;
    void        reject() override;
    void        closeEvent(QCloseEvent *) override;

private:
    int         m_status {Status::NO};
};
