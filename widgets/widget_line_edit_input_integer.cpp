#include "widget_line_edit_input_integer.h"

IntegerInputLineEdit::IntegerInputLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    set(0);
}

int IntegerInputLineEdit::get() const {
    bool ok = false;
    int value = text().toInt(&ok);
    return ok ? value : 0;
}

void IntegerInputLineEdit::set(const int value) {
    setText(QString::number(value));
}

bool IntegerInputLineEdit::isValid(QString &) const {
    bool ok = false;
    text().toInt(&ok);
    return ok;
}
