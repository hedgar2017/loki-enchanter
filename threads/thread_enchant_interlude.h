#pragma once

#include "thread_enchant.h"
#include "interfaces/i_observable.h"

#include <memory>
#include <QSharedPointer>

#include "application.h"
#include "ocr/ocr.h"
#include "devices/mouse.h"

class InterludeEnchantThread : public EnchantThread, IObservable
{
    Q_OBJECT

public:
    explicit InterludeEnchantThread(const std::shared_ptr<Application> &p_app, QObject *parent = nullptr);
    InterludeEnchantThread(const InterludeEnchantThread &) = delete;
    void operator =(const InterludeEnchantThread &) = delete;
    virtual ~InterludeEnchantThread() override = default;

    virtual void                        run() override;
    virtual void                        initialize() override;
    virtual void                        abort() override;
    virtual void                        onEvent() override;

private:
    virtual int                         getCurrentItemLevel();
    virtual QPoint                      getItemPoint() const;
    virtual void                        moveCursor(const QPoint &);
    virtual void                        relogin();
    virtual void                        sendReport(const QString &message);
    virtual void                        sendPreview(const QPixmap &pixmap, const QString &text);

    std::shared_ptr<Application>        mp_app;
    std::unique_ptr<Mouse>              mp_mouse;
    std::unique_ptr<OCR>                mp_ocr;

    int                                 m_currentItem               {0};
    int                                 m_currentLevel              {ITEM_LEVEL_INVALID};

    static const int                    ITEM_LEVEL_ZERO             {0};
    static const int                    ITEM_LEVEL_INVALID          {-1};
    static const int                    ITEMS_IN_A_ROW              {6};
    static const int                    ITEM_HORIZONTAL_OFFSET      {37};
    static const int                    ITEM_VERTICAL_OFFSET        {35};

    static const int                    GENERIC_DELAY_MS            {100};
};
