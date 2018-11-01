#pragma once

#include <QProgressBar>

class ItemProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit ItemProgressBar(QWidget *parent = nullptr);
    ItemProgressBar(const ItemProgressBar &) = delete;
    void operator =(const ItemProgressBar &) = delete;
    virtual ~ItemProgressBar() = default;

    void setData(const int min, const int val, const int max);
};
