//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H

#include <QByteArray>
#include <QList>
#include <QFile>
#include <cmath>
#include <QDebug>
#include <QCryptographicHash> // to use sha256

#define ENDLINE "#_end_#"
#define KEY_GEN_LIMIT 10

static const QString SIGN_MARKER = "-SIGN-";
static const int signMarkerLength = SIGN_MARKER.length();

typedef QCryptographicHash::Algorithm HashAlgorithm;

class QRSAEncryption
{

public:
    enum Rsa {
        RSA_64 = 64,
        RSA_128 = 128
    };

    QRSAEncryption();

    unsigned int getBytesSize(QRSAEncryption::Rsa rsa);

// static methods
    static bool generatePairKeyS(QByteArray &pubKey, QByteArray &privKey,
                                 QRSAEncryption::Rsa rsa);
    static QByteArray encodeS(const QByteArray &rawData, const QByteArray &pubKey);
    static QByteArray decodeS(const QByteArray &rawData, const QByteArray &privKey);
    static QByteArray signMessageS(QByteArray rawData, const QByteArray &privKey);
    static bool checkSignMessageS(const QByteArray &rawData, const QByteArray &pubKey);

// non-static methods
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey,
                         QRSAEncryption::Rsa rsa);
    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey);
    QByteArray signMessage(QByteArray rawData, const QByteArray &privKey);
    bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey);

private:
    bool testKeyPair(const QByteArray &pubKey, const QByteArray &privKey);
};

#endif // QRSAENCRYPTION_H
