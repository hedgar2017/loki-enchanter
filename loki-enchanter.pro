#==============================================================#
#                                                              #
#   DESCRIPTION: New generation Lineage 2 auto-clicker         #
#                                                              #
#  REQUIREMENTS: L2LokiVHID virtual mouse driver               #
#                Windows 7 x64 and higher                      #
#                                                              #
#        AUTHOR: Alex Zarudnyy (hedgar), hedgar2017@gmail.com  #
#                                                              #
#==============================================================#

QT += core gui widgets network

TARGET = L2Loki
TEMPLATE = app

DEFINES += \
    QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x050000

LIBS += \
    user32.lib \
    cfgmgr32.lib \
    advapi32.lib \
    hid.lib
CONFIG(debug, debug|release) {
    LIBS += \
        $$OUT_PWD/debug/liblept.lib \
        $$OUT_PWD/debug/libtesseract.lib
}
CONFIG(release, debug|release) {
    LIBS += \
        $$OUT_PWD/release/liblept.lib \
        $$OUT_PWD/release/libtesseract.lib
}

HEADERS += \
    application.h \
    main_window.h \
    widgets/widget_group_box_wrapper.h \
    widgets/widget_progress_bar_item.h \
    widgets/widget_line_edit_input_integer.h \
    widgets/widget_input_qrect.h \
    widgets/widget_input_qpoint.h \
    widgets/widget_settings_enchant.h \
    widgets/widget_settings_macro.h \
    widgets/widget_settings_ocr.h \
    widgets/widget_settings_relogin.h \
    widgets/widget_settings_window.h \
    widgets/widget_settings_locale.h \
    dialogs/dialog_confirm_save.h \
    dialogs/dialog_input_screen_point.h \
    dialogs/dialog_settings.h \
    dialogs/dialog_input_screen_rect.h \
    dialogs/dialog_about.h \
    interfaces/i_observable.h \
    interfaces/i_observer.h \
    interfaces/i_jsonable.h \
    models/model_enchant.h \
    models/model_macro.h \
    models/model_relogin.h \
    models/model_ocr.h \
    models/model_window.h \
    models/model_locale.h \
    threads/thread_enchant.h \
    threads/thread_enchant_interlude.h \
    tesseract/apitypes.h \
    tesseract/baseapi.h \
    tesseract/basedir.h \
    tesseract/capi.h \
    tesseract/errcode.h \
    tesseract/fileerr.h \
    tesseract/genericvector.h \
    tesseract/helpers.h \
    tesseract/host.h \
    tesseract/ltrresultiterator.h \
    tesseract/memry.h \
    tesseract/ndminx.h \
    tesseract/ocrclass.h \
    tesseract/osdetect.h \
    tesseract/pageiterator.h \
    tesseract/params.h \
    tesseract/platform.h \
    tesseract/publictypes.h \
    tesseract/renderer.h \
    tesseract/resultiterator.h \
    tesseract/serialis.h \
    tesseract/strngs.h \
    tesseract/tesscallback.h \
    tesseract/thresholder.h \
    tesseract/unichar.h \
    tesseract/unicharmap.h \
    tesseract/unicharset.h \
    devices/device.h \
    devices/mouse.h \
    ocr/ocr.h \
    ocr/ocr_processed.h \
    screenshot/screenshot.h \
    services/service_registry.h \
    services/service_storage.h \
    services/service_hook.h \
    interfaces/i_applyable.h \
    interfaces/i_validable.h \
    crypto/crypto.h \
    services/service_bcdedit.h \
    widgets/widget_settings_device.h \
    dialogs/dialog_confirm_reboot.h \
    services/service_devcon.h

SOURCES += \
    main.cpp \
    application.cpp \
    main_window.cpp \
    models/model_enchant.cpp \
    models/model_macro.cpp \
    models/model_ocr.cpp \
    models/model_relogin.cpp \
    models/model_window.cpp \
    models/model_locale.cpp \
    threads/thread_enchant.cpp \
    threads/thread_enchant_interlude.cpp \
    widgets/widget_group_box_wrapper.cpp \
    widgets/widget_progress_bar_item.cpp \
    widgets/widget_line_edit_input_integer.cpp \
    widgets/widget_input_qrect.cpp \
    widgets/widget_input_qpoint.cpp \
    widgets/widget_settings_enchant.cpp \
    widgets/widget_settings_macro.cpp \
    widgets/widget_settings_ocr.cpp \
    widgets/widget_settings_relogin.cpp \
    widgets/widget_settings_window.cpp \
    widgets/widget_settings_locale.cpp \
    dialogs/dialog_about.cpp \
    dialogs/dialog_settings.cpp \
    dialogs/dialog_input_screen_rect.cpp \
    dialogs/dialog_confirm_save.cpp \
    dialogs/dialog_input_screen_point.cpp \
    devices/device.cpp \
    devices/mouse.cpp \
    ocr/ocr.cpp \
    ocr/ocr_processed.cpp \
    screenshot/screenshot.cpp \
    services/service_registry.cpp \
    services/service_storage.cpp \
    services/service_hook.cpp \
    crypto/crypto.cpp \
    services/service_bcdedit.cpp \
    widgets/widget_settings_device.cpp \
    dialogs/dialog_confirm_reboot.cpp \
    services/service_devcon.cpp

DISTFILES += \
    .gitignore \
    app.rc \
    translations/en_US.ts \
    translations/uk_UA.ts \
    translations/ru_RU.ts

RC_FILE = app.rc
RESOURCES += app.qrc
TRANSLATIONS += \
    translations/en_US.ts \
    translations/uk_UA.ts \
    translations/ru_RU.ts
