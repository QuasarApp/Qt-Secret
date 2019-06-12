//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QByteArray>
#include <qrsaencryption.h>
#include <QDateTime>
#include <qdebug.h>
#include <cmath>

const int testSize = 100;

QByteArray randomArray() {
    srand(static_cast<unsigned int>(time(nullptr)));
    QByteArray res;

    int length = rand() % 124 * 1;

    for (int i = 0; i < length; ++i) {
        res.push_back(static_cast<char>(rand() % 0xFF));
    }

    return res;
}

bool testCrypto(QRSAEncryption::Rsa rsa) {

    QByteArray pub, priv;
    QRSAEncryption e;

    for (int i = 0; i < testSize; i++) {
        e.generatePairKeyS(pub, priv, rsa);

        qInfo() << QString("Test keys (%0/%1):").arg(i).arg(testSize);
        qInfo() << QString("Private key: %0").arg(QString(priv.toHex()));
        qInfo() << QString("Public key: %0").arg(QString(pub.toHex()));

        if (pub.size() != rsa / 4) {
            qCritical() << "pubKey size wrong RSA" << rsa;
            return false;
        }

        if (priv.size() != rsa / 4) {
            qCritical() << "privKey size wrong RSA" << rsa;
            return false;
        }

        for (int i = 0; i < testSize; i++) {
            auto base = randomArray();

            auto encodeData = e.encode(base, pub);
            auto decodeData = e.decode(encodeData, priv);

            if ( base != decodeData) {
                qCritical() << "encode/decode data error RSA" << rsa;
                return false;
            }

            encodeData = e.signMessage(base, priv);

            if (!e.checkSignMessage(encodeData, pub)) {
                qCritical() << "sig message error RSA" << rsa;
                return false;
            }

            encodeData += "work it";

            if (e.checkSignMessage(encodeData, pub)) {
                qCritical() << "sig message error RSA with added value to back" << rsa;
                return false;
            }

            encodeData.push_front("not work");

            if (e.checkSignMessage(encodeData, pub)) {
                qCritical() << "sig message error RSA with added value to front" << rsa;
                return false;
            }
        }
    }

    return true;
}

int main() {

    if(!testCrypto(QRSAEncryption::Rsa::RSA_64)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_128)) {
        return 1;
    }

    qInfo() << "Tests passed successfully";

    return 0;
}
