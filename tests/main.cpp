//#
//# Copyright (C) 2018-2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QByteArray>
#include <qrsaencryption.h>
#include <QDateTime>
#include <qdebug.h>
#include <cmath>
#include <time.h>
#include <iostream>

//const int testSize = 20;
static const QHash <int,int > testSize = {
    {QRSAEncryption::RSA_64, 128},
    {QRSAEncryption::RSA_128, 64},
    {QRSAEncryption::RSA_256, 32},
    {QRSAEncryption::RSA_512, 16},
    {QRSAEncryption::RSA_1024, 8},
    {QRSAEncryption::RSA_2048, 4},
    {QRSAEncryption::RSA_4096, 2},
    {QRSAEncryption::RSA_8192, 1}
};

QByteArray randomArray(int length = -1) {
    srand(static_cast<unsigned int>(time(nullptr)));
    QByteArray res;

    if (length == -1) {
        length = rand() % 124 * 1;
    }

    for (int i = 0; i < length; ++i) {
        res.push_back(static_cast<char>(rand() % 0xFD) + 1);
    }

    return res;
}

void print(const QString& str) {
    std::cout << str.toStdString() << std::endl;
}

bool checkKeys(const QByteArray& pubKey, const QByteArray& privKey,
               QRSAEncryption::Rsa rsa) {
    QRSAEncryption e(rsa);

    print( QString("Private key: %0").arg(QString(pubKey.toHex())));
    print( QString("Public key: %0").arg(QString(privKey.toHex())));

    if (pubKey.size() != rsa / 4) {
        print("pubKey size wrong RSA" + QString::number(rsa));
        return false;
    }

    if (privKey.size() != rsa / 4) {
        print("privKey size wrong RSA" + QString::number(rsa));
        return false;
    }

    for (int i = 0; i < testSize[rsa]; i++) {
        auto base = randomArray();

        auto encodeData = e.encode(base, pubKey);
        auto decodeData = e.decode(encodeData, privKey);

        if ( base != decodeData) {
            print("encode/decode data error RSA" + QString::number(rsa));
            return false;
        }

        encodeData = e.signMessage(base, privKey);

        if (!e.checkSignMessage(encodeData, pubKey)) {
            print("sig message error RSA" + QString::number(rsa));
            return false;
        }

        encodeData += "work it";

        if (e.checkSignMessage(encodeData, pubKey)) {
            print("sig message error RSA with added value to back" + QString::number(rsa));
            return false;
        }

        encodeData.push_front("not work");

        if (e.checkSignMessage(encodeData, pubKey)) {
            print("sig message error RSA with added value to front" + QString::number(rsa));
            return false;
        }
    }

    return true;
}


bool testCrypto(QRSAEncryption::Rsa rsa) {

    QByteArray pub, priv;
    QRSAEncryption e(rsa);

    for (int i = 0; i < testSize[rsa]; i++) {

        print(QString("Test RSA-%0 (%1/%2):").arg(rsa).arg(i + 1).arg(testSize[rsa]));

        if (!e.generatePairKey(pub, priv)) {
            print( "key not generated RSA" + QString::number(rsa));
            return false;
        }

        if (!checkKeys(pub, priv, rsa)) {
            return false;
        }
    }

    return true;
}

bool testExample() {
    QByteArray pub, priv;
    QRSAEncryption e(QRSAEncryption::Rsa::RSA_2048);
    e.generatePairKey(pub, priv); // or other rsa size

    QByteArray msg = "test message";

    auto signedMessage = e.signMessage(msg, priv);

    if (e.checkSignMessage(signedMessage, pub)) {
        print(" message signed success");
        return true;
    }

    return false;

}

bool testGetKeyRsaType() {
    print("Check GetKeyRsaType function");

    QByteArray pub, priv;
    QRSAEncryption e(QRSAEncryption::Rsa::RSA_512);
    e.generatePairKey(pub, priv); // or other rsa size

    QByteArray invalidKey, validSizeKey;

    invalidKey = randomArray();

    validSizeKey = randomArray(
                static_cast<int>(
                    QRSAEncryption::getKeyBytesSize(QRSAEncryption::Rsa::RSA_512)));

    if (QRSAEncryption::getKeyRsaType(pub) != QRSAEncryption::Rsa::RSA_512) {
        return false;
    }

    if (QRSAEncryption::getKeyRsaType(priv) != QRSAEncryption::Rsa::RSA_512) {
        return false;
    }

    if (QRSAEncryption::getKeyRsaType(invalidKey) != QRSAEncryption::Rsa::Invalid) {
        return false;
    }
    print("success");
    return true;
}

bool testEncryptAndDecryptExample() {

    QByteArray pub, priv;
    QRSAEncryption e(QRSAEncryption::Rsa::RSA_2048);
    e.generatePairKey(pub, priv); // or other rsa size

    QByteArray msg = "test message";

    auto encryptMessage = e.encode(msg, pub);

    if (encryptMessage == msg)
        return false;

    auto decodeMessage = e.decode(encryptMessage, priv);

    return decodeMessage == msg;
}

int main() {

    if (!testGetKeyRsaType()) {
        return 1;
    }

    if(!testExample()) {
        return 1;
    }

    if (!testEncryptAndDecryptExample()) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_64)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_128)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_256)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_512)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_1024)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_2048)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_4096)) {
        return 1;
    }

    print("Tests passed successfully");

    return 0;
}
