#include "widget_settings_enchant.h"

#include <QGridLayout>
#include <QMessageBox>

#include <stdexcept>

#include "widget_group_box_wrapper.h"

EnchantSettingsWidget::EnchantSettingsWidget(EnchantModel &model, QWidget *parent)
    : QWidget{parent}
    , mr_model{model}

    , mw_itemAmountInput{new IntegerInputLineEdit{this}}
    , mw_skipItemsInput{new IntegerInputLineEdit{this}}
    , mw_itemLevelInput{new IntegerInputLineEdit{this}}
    , mw_scrollCooldownInput{new IntegerInputLineEdit{this}}
    , mw_delayBeforeStartInput{new IntegerInputLineEdit{this}}
    , mw_itemSignatureListTextEdit{new QTextEdit{this}}
    , mw_isGlobalStopHookEnabledCheckBox{new QCheckBox{this}}

    , mw_resetPushButton{new QPushButton{this}}
{
    QGridLayout *layout = new QGridLayout{this};
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemLevelInput),             0, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_skipItemsInput),             1, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemAmountInput),            2, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_scrollCooldownInput),        3, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_delayBeforeStartInput),      4, 0);
    layout->addWidget(SET_GROUP_BOX_WRAPPER(mw_itemSignatureListTextEdit),  5, 0);
    layout->addWidget(mw_isGlobalStopHookEnabledCheckBox,                   6, 0);
    layout->addWidget(mw_resetPushButton,                                   7, 0);

    GET_GROUP_BOX_WRAPPER(mw_itemAmountInput)->setTitle(tr("INPUT_ITEM_AMOUNT_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_skipItemsInput)->setTitle(tr("INPUT_SKIP_ITEMS_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_itemLevelInput)->setTitle(tr("INPUT_ITEM_LEVEL_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_scrollCooldownInput)->setTitle(tr("INPUT_SCROLL_COOLDOWN_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_delayBeforeStartInput)->setTitle(tr("INPUT_DELAY_BEFORE_START_TITLE"));
    GET_GROUP_BOX_WRAPPER(mw_itemSignatureListTextEdit)->setTitle(tr("TEXT_EDIT_ITEM_SIGNATURE_LIST_TITLE"));
    mw_isGlobalStopHookEnabledCheckBox->setText(tr("CHECK_BOX_IS_GLOBAL_STOP_HOOK_ENABLED_TEXT"));
    mw_resetPushButton->setText(tr("PUSH_BUTTON_RESET_TEXT"));

    setLayout(layout);
    reset();

    connect(mw_resetPushButton, &QPushButton::clicked, this, &EnchantSettingsWidget::reset);
}

void EnchantSettingsWidget::apply()
{
    QString error;
    if (!isValid(error)) {
        throw std::runtime_error(error.toStdString());
    }

    mr_model.setItemAmount(mw_itemAmountInput->get());
    mr_model.setSkipItems(mw_skipItemsInput->get());
    mr_model.setItemLevel(mw_itemLevelInput->get());
    mr_model.setScrollCooldown(mw_scrollCooldownInput->get());
    mr_model.setDelayBeforeStart(mw_delayBeforeStartInput->get());
    mr_model.setItemSignatureList(mw_itemSignatureListTextEdit->document()->toPlainText().split(QRegExp("[\r\n]"), QString::SkipEmptyParts));
    mr_model.setGlobalStopHookEnabled(mw_isGlobalStopHookEnabledCheckBox->isChecked());
}

bool EnchantSettingsWidget::isValid(QString &error) const
{
    QStringList errorList;
    bool isValid = true;
    if (!mw_itemAmountInput->isValid(error) || mw_itemAmountInput->get() <= 0) {
        errorList << tr("ERROR_ITEM_AMOUNT_INVALID");
        isValid = false;
    }
    if (!mw_skipItemsInput->isValid(error) || mw_skipItemsInput->get() < 0) {
        errorList << tr("ERROR_SKIP_ITEMS_INVALID");
        isValid = false;
    }
    if (!mw_itemLevelInput->isValid(error) || mw_itemLevelInput->get() <= 0) {
        errorList << tr("ERROR_ITEM_LEVEL_INVALID");
        isValid = false;
    }
    if (!mw_scrollCooldownInput->isValid(error) || mw_scrollCooldownInput->get() < 0) {
        errorList << tr("ERROR_SCROLL_COOLDOWN_INVALID");
        isValid = false;
    }
    if (!mw_delayBeforeStartInput->isValid(error) || mw_delayBeforeStartInput->get() < 0) {
        errorList << tr("ERROR_DELAY_BEFORE_START_INVALID");
        isValid = false;
    }
    error += errorList.join("\r\n");
    return isValid;
}

void EnchantSettingsWidget::reset() {
    mw_itemAmountInput->set(mr_model.getItemAmount());
    mw_skipItemsInput->set(mr_model.getSkipItems());
    mw_itemLevelInput->set(mr_model.getItemLevel());
    mw_scrollCooldownInput->set(mr_model.getScrollCooldown());
    mw_delayBeforeStartInput->set(mr_model.getDelayBeforeStart());

    mw_itemSignatureListTextEdit->clear();
    foreach (const QString &s, mr_model.getItemSignatureList()) mw_itemSignatureListTextEdit->append(s);

    mw_isGlobalStopHookEnabledCheckBox->setChecked(mr_model.isGlobalStopHookEnabled());
}
