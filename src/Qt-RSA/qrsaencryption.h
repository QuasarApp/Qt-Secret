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
#include <QCryptographicHash> // to use sha256

#define ENDLINE "#_end_#"

class QRSAEncryption
{
private:
    bool testKeyPair(const QByteArray &pubKey, const QByteArray &privKey);
public:

    enum Rsa {
        RSA_64 = 64,
        RSA_128 = 128
    };

    QRSAEncryption();

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey);

    QByteArray signMessage(QByteArray rawData, const QByteArray &privKey);
    bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey);

    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey, Rsa = RSA_128);

    static unsigned int getBytesSize(Rsa rsa);

};

#endif // QRSAENCRYPTION_H
