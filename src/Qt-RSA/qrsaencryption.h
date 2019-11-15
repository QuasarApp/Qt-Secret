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
#include "./../qtsecret_global.h"

#include <bigint.h>

typedef BigInt INT;

#define KEY_GEN_LIMIT 10

static const QString SIGN_MARKER = "-SIGN-";
static const int signMarkerLength = SIGN_MARKER.length();

typedef QCryptographicHash::Algorithm HashAlgorithm;

class Qt_SECRETSHARED_EXPORT QRSAEncryption
{
public:

    enum Rsa {
        Invalid = 0,
        RSA_64 = 64,
        RSA_128 = 128,
        RSA_256 = 256,
        RSA_512 = 512,
        RSA_1024 = 1024,
        RSA_2048 = 2048,
        RSA_4096 = 4096,
        RSA_8192 = 8192,

    };

    enum BlockSize {
        Auto = 0, // fast but not stable. (using by default)
        OneByte = 1 // stable but slow. (using for sig and check sig messages)
    };


    QRSAEncryption(Rsa rsa = Rsa::RSA_256);

// static methods

    // OLDMETHODS DELETE IN next Version
    static bool generatePairKeyS(QByteArray &pubKey, QByteArray &privKey,
                                 QRSAEncryption::Rsa rsa = RSA_256);
    static QByteArray encodeS(const QByteArray &rawData, const QByteArray &pubKey,
                              Rsa rsa = RSA_256, BlockSize blockSizeMode = BlockSize::Auto);
    static QByteArray decodeS(const QByteArray &rawData, const QByteArray &privKey,
                              Rsa rsa = RSA_256, BlockSize blockSizeMode = BlockSize::Auto);
    static QByteArray signMessageS(QByteArray rawData, const QByteArray &privKey,
                                   Rsa rsa = RSA_256);
    static bool checkSignMessageS(const QByteArray &rawData, const QByteArray &pubKey,
                                        Rsa rsa);
    // OLDMETHODS END

    static bool generatePairKey(QByteArray &pubKey, QByteArray &privKey,
                                 QRSAEncryption::Rsa rsa);
    static QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey,
                              Rsa rsa, BlockSize blockSizeMode = BlockSize::Auto);
    static QByteArray decode(const QByteArray &rawData, const QByteArray &privKey,
                              Rsa rsa, BlockSize blockSizeMode = BlockSize::Auto);
    static QByteArray signMessage(QByteArray rawData, const QByteArray &privKey,
                                   Rsa rsa);
    static bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey,
                                  Rsa rsa);
    static bool isValidRsaKey(const QByteArray& key);
    static unsigned int getKeyBytesSize(QRSAEncryption::Rsa rsa);

// non-static methods
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey);

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey,
                      BlockSize blockSizeMode = BlockSize::Auto);

    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey,
                      BlockSize blockSizeMode = BlockSize::Auto);

    QByteArray signMessage(QByteArray rawData, const QByteArray &privKey);

    bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey);

    Rsa getRsa() const;
    QByteArray convertPublic(const QByteArray& sslKey) const;
    QByteArray convertPrivate(const QByteArray& sslKey, const QByteArray& pass = "") const;
    QByteArray convertFromSsl(QByteArray sslKey, const QByteArray &pass = "") const;

private:

    Rsa _rsa;

    bool testKeyPair(const QByteArray &pubKey, const QByteArray &privKey);
    bool isMutuallyPrime(const INT &a, const INT &b);
    Rsa getBitsSize(const INT& i) const;
    Rsa getBitsSize(const QByteArray& array) const;

    INT fromArray(const QByteArray& array) const;
    QByteArray toArray(const INT &i, short sizeBlok = -1);
    INT randomNumber(bool fullFilled = true) const;
    INT toPrime(INT) const;
    INT randomPrimeNumber(INT no = 0) const;
    INT extEuclid(INT a, INT b) const;

    short getBlockSize(INT i) const;

    QByteArray encodeBlok(const INT& block, const INT& e, const INT& m, short blockSize);
    QByteArray decodeBlok(const INT& block, const INT& d, const INT& m, short blockSize);


};

#endif // QRSAENCRYPTION_H
