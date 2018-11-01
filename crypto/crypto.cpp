#include "crypto.h"

#include <random>
#include <QStringList>

QString Crypto::encryptPassword(const QString &data)
{
    return QString::fromUtf8(xorCypher(data.toLocal8Bit()).toBase64());
}

QString Crypto::decryptPassword(const QString &data)
{
    return QString::fromUtf8(xorCypher(QByteArray::fromBase64(data.toLocal8Bit())));
}

quint64 Crypto::decryptMac(const QString &data)
{
    QString hex = QString::fromUtf8(QByteArray::fromBase64(data.toLocal8Bit()));
    quint64 mac = 0;

    for (int i = 0; i < 4; ++i) {
        quint64 value = hex.mid(i * 16, 16).toULongLong(nullptr, 16);
        for (int j = 0; j < 16; ++j) {
            if (value & HIGHEST >> (j * 4 + 3)) {
                mac |= HIGHEST >> (i * 16 + j);
            }
        }
    }

    return mac;
}

QString Crypto::encryptMac(const quint64 data)
{
    std::random_device device;
    std::default_random_engine generator{device()};
    std::uniform_int_distribution<quint64> distribution{0, _UI64_MAX};
    quint64 array[4] = {distribution(generator), distribution(generator), distribution(generator), distribution(generator)};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (data & (HIGHEST >> (i * 16 + j))) {
                array[i] |= HIGHEST >> (j * 4 + 2);
            } else {
                array[i] &= ~(HIGHEST >> (j * 4 + 2));
            }
        }
    }

    QString hex = QString{"%1%2%3%4"}
            .arg(array[0], 16, 16, QChar{'0'})
            .arg(array[1], 16, 16, QChar{'0'})
            .arg(array[2], 16, 16, QChar{'0'})
            .arg(array[3], 16, 16, QChar{'0'});
    return QString::fromUtf8(hex.toUtf8().toBase64());
}

std::vector<quint64> Crypto::encryptMacDrv(const quint64 data)
{
    std::random_device device;
    std::default_random_engine generator{device()};
    std::uniform_int_distribution<quint64> distribution{0, _UI64_MAX};

    std::vector<quint64> array;
    for (int i = 0; i < 4; ++i) {
        array.push_back(distribution(generator));
        for (int j = 0; j < 16; ++j) {
            if (data & (HIGHEST >> (i * 16 + j))) {
                array[i] |= HIGHEST >> (j * 4 + 1);
            } else {
                array[i] &= ~(HIGHEST >> (j * 4 + 1));
            }
        }
    }
    return array;
}

QString Crypto::randomAlphanumeric(const int length)
{
    const QString possibleCharacters{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};

    QString randomString;
    for (int i = 0; i < length; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

QString Crypto::randomBase64(const int length)
{
    const QString possibleCharacters{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

    QString randomString;
    for (int i = 0; i < length; ++i) {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

QByteArray Crypto::xorCypher(const QByteArray &array)
{
    QByteArray result;
    for (int i = 0; i < array.size(); ++i) {
        result.append(array[i] ^ (41 + i ^ 7));
    }
    return result;
}
