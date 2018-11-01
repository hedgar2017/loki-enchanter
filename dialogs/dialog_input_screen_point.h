#pragma once

#include <QDialog>
#include <QPoint>

class ScreenPointInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreenPointInputDialog(QWidget *parent = nullptr);
    ScreenPointInputDialog(const ScreenPointInputDialog &) = delete;
    void operator =(const ScreenPointInputDialog &) = delete;
    virtual ~ScreenPointInputDialog() override = default;

    const QPoint&       getSelectedPoint() const;

protected:
    void                mouseReleaseEvent(QMouseEvent *) override;

private:
    QPoint              m_selectedPoint;
};
