#pragma once

#include <vector>
#include <QString>
#include <QByteArray>

class Crypto
{

public:
    static QString                      encryptPassword(const QString &);
    static QString                      decryptPassword(const QString &);

    static quint64                      decryptMac(const QString &);
    static QString                      encryptMac(const quint64);
    static std::vector<quint64>         encryptMacDrv(const quint64);

    static QString                      randomAlphanumeric(const int length);
    static QString                      randomBase64(const int length);

private:
    static QByteArray                   xorCypher(const QByteArray &);

    static const quint64                HIGHEST {static_cast<quint64>(1) << 63};
};
