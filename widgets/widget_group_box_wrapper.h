#pragma once

#include <QGroupBox>

class GroupBoxWrapper : public QGroupBox
{
    Q_OBJECT

public:
    explicit GroupBoxWrapper(QWidget *wrapped, QWidget *parent = nullptr);
    GroupBoxWrapper(const GroupBoxWrapper &) = delete;
    void operator =(const GroupBoxWrapper &) = delete;
    virtual ~GroupBoxWrapper() = default;
};

// UNSAFE! Use only just like you see in the example!
#define SET_GROUP_BOX_WRAPPER(wrapped) new GroupBoxWrapper(wrapped, this)
#define GET_GROUP_BOX_WRAPPER(wrapped) static_cast<QGroupBox *>(wrapped->parent())
