#pragma once

#include <QLineEdit>
#include "interfaces/i_validable.h"

class IntegerInputLineEdit : public QLineEdit, public IValidable
{
    Q_OBJECT

public:
    explicit IntegerInputLineEdit(QWidget *parent = nullptr);
    IntegerInputLineEdit(const IntegerInputLineEdit &) = delete;
    void operator =(const IntegerInputLineEdit &) = delete;
    virtual ~IntegerInputLineEdit() = default;

    int             get() const;
    void            set(const int);
    bool            isValid(QString &error) const override;
};
