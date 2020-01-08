//#
//# Copyright (C) 2018-2020 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qrsaencryption.h"

#include <QString>
#include <iostream>
#include <ctime>
#include <chrono>
#include <QTextStream>

#define KEY_GEN_LIMIT 10

const QString SIGN_MARKER = "-SIGN-";
const int signMarkerLength = SIGN_MARKER.length();

QRSAEncryption::INT eulerFunc(const QRSAEncryption::INT &p, const QRSAEncryption::INT &q) {
    return (p - 1) * (q - 1);
}

bool QRSAEncryption::isMutuallyPrime(const INT &a, const INT &b) {
    if (        (!(a % 2) && !(b % 2))
                || (!(a % 3) && !(b % 3))
                || (!(a % 5) && !(b % 5))
                || (!(a % 7) && !(b % 7))
                ) return false;

    return INT().gcd(a, b) == 1;
}

QRSAEncryption::Rsa QRSAEncryption::getBitsSize(const INT &i) const {
    int rsaBits = RSA_64;
    int intBits = i.sizeBits();

    while (rsaBits < intBits) {
        rsaBits *= 2;
    }

    return static_cast<QRSAEncryption::Rsa>(rsaBits);

}

QRSAEncryption::Rsa QRSAEncryption::getBitsSize(const QByteArray &key) const {
    if (isValidRsaKey(key)) {
        return static_cast<QRSAEncryption::Rsa>(key.size() * 4);
    }

    return QRSAEncryption::Rsa::Invalid;
}

QRSAEncryption::INT QRSAEncryption::fromArray(const QByteArray &array) const {
    INT res = 0;
    res.fromHex(array.toHex().toStdString());
    return res;
}

QByteArray QRSAEncryption::toArray(const INT &i, short sizeBlok) {
    QByteArray res;
    res = QByteArray::fromHex(QByteArray::fromStdString(i.getString(16)));

    if (sizeBlok < 0) {
        return res;
    }

    while (res.size() < sizeBlok) {
        res.push_front(char(0));
    }

    return res.left(sizeBlok);
}

QRSAEncryption::INT QRSAEncryption::randomNumber(bool fullFill) const {

    srand(std::chrono::duration_cast<std::chrono::nanoseconds>
          (std::chrono::system_clock::now().time_since_epoch()).count()
          % std::numeric_limits<int>::max());

    INT res{1};

    if(fullFill) {

        while(res.longBits() < _rsa) {
            res *= (rand() % (std::numeric_limits<int>::max() - 1)) + 1;
        }
    } else {

        int longDiff = _rsa / (sizeof (int) * 8);

        while (longDiff > 0) {
            longDiff--;
            res *= (rand() % (std::numeric_limits<int>::max() - 1)) + 1;
        }
    }

    return res;
}

QRSAEncryption::INT QRSAEncryption::toPrime(INT n) const {
    if (!(n % 2)) {
        ++n;
    }

    INT LN = n;
    INT RN = n;

    while (true) {

        if (LN.isPrime(false)) return LN;

        RN+=2;

        if (RN.isPrime(false)) return RN;
        LN-=2;
    }
}

QRSAEncryption::INT QRSAEncryption::randomPrimeNumber(INT no) const {
    srand(static_cast<unsigned int>(time(nullptr)));

    // max INT
    INT max('1', _rsa / 2, 2);

    auto p = toPrime(randomNumber() % max);
    while(p == no) p = toPrime(randomNumber() % max);

    return p;
}

QRSAEncryption::INT QRSAEncryption::extEuclid(INT a, INT b) const {
    INT x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
    while (a != 0) {
        q = gcd / a;
        r = gcd % a;
        m = x - u * q;
        n = y - v * q;
        gcd = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    return y;
}

short QRSAEncryption::getBlockSize(INT i) const {
    return static_cast<short>(i.longBytes()) - 1;
}

QByteArray QRSAEncryption::encodeBlok(const INT &block, const INT &e, const INT &m, short blockSize) {

    return toArray(INT::powm(block, e, m), blockSize);
}

QByteArray QRSAEncryption::decodeBlok(const INT &block, const INT &d, const INT &m, short blockSize) {

    return toArray(INT::powm(block, d, m), blockSize);
}

QRSAEncryption::QRSAEncryption(Rsa rsa) {
    _rsa = rsa;
}

unsigned int QRSAEncryption::getKeyBytesSize(QRSAEncryption::Rsa rsa) {

    return rsa / 4;
}

QRSAEncryption::Rsa QRSAEncryption::getKeyRsaType(const QByteArray &key) {
    if (QRSAEncryption::isValidRsaKey(key)) {
        auto res = static_cast<int>(QRSAEncryption::Rsa::RSA_64);
        for ( ;res <= QRSAEncryption::Rsa::RSA_8192; res *= 2 ) {
            if (static_cast<unsigned int>(key.size()) == getKeyBytesSize(static_cast<QRSAEncryption::Rsa>(res))) {
                return static_cast<QRSAEncryption::Rsa>(res);
            }
        }
    }

    return QRSAEncryption::Rsa::Invalid;
}

// --- static methods ---
bool QRSAEncryption::generatePairKey(QByteArray &pubKey, QByteArray &privKey,
                                      QRSAEncryption::Rsa rsa) {

    return QRSAEncryption(rsa).generatePairKey(pubKey, privKey);
}

QByteArray QRSAEncryption::encode(const QByteArray &rawData, const QByteArray &pubKey,
                                   Rsa rsa, BlockSize blockSizeMode) {

    return QRSAEncryption(rsa).encode(rawData, pubKey, blockSizeMode);
}

QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey,
                                   Rsa rsa, BlockSize blockSizeMode) {

    return QRSAEncryption(rsa).decode(rawData, privKey, blockSizeMode);
}

QByteArray QRSAEncryption::signMessage(QByteArray rawData, const QByteArray &privKey, Rsa rsa) {

    return QRSAEncryption(rsa).signMessage(rawData, privKey);
}

bool QRSAEncryption::checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey, Rsa rsa) {

    return QRSAEncryption(rsa).checkSignMessage(rawData, pubKey);
}

// --- end of static methods ---

bool QRSAEncryption::generatePairKey(QByteArray &pubKey, QByteArray &privKey) {

    int cnt{0};
    bool keyGenRes{false};
    INT p, q, modul, eilor, e, d;
    do {

        pubKey.clear();
        privKey.clear();

        p = randomPrimeNumber();
        q = randomPrimeNumber(p);

        modul = 0;
        while ((modul = p * q) < 0) {
            p = toPrime((p - 1) / 2);
        }

        eilor = eulerFunc(p, q);
        e = randomNumber() % eilor;

        if (!(e % 2)) --e;

        do {
            e -= 2;
        } while((!isMutuallyPrime(eilor, e)));

        d = extEuclid(eilor , e);

        while(d < 0 ) {
            d += eilor;
        }

        pubKey.append(toArray(e, _rsa / 8));
        pubKey.append(toArray(modul, _rsa / 8));
        privKey.append(toArray(d, _rsa / 8));
        privKey.append(toArray(modul, _rsa / 8));

    } while (!(keyGenRes = testKeyPair(pubKey, privKey)) && (++cnt < KEY_GEN_LIMIT));

    if(cnt >= KEY_GEN_LIMIT) qWarning() << QString("(Warning): Exceeded limit of key generation (%0)!").arg(KEY_GEN_LIMIT);

    return (keyGenRes && cnt < KEY_GEN_LIMIT);
}

// --- non-static methods ---
QByteArray QRSAEncryption::encode(const QByteArray &rawData, const QByteArray &pubKey, BlockSize blockSizeMode) {

    if (getBitsSize(pubKey) != _rsa) {
        return QByteArray();
    }

    int index = 0;

    QByteArray block;

    INT e = fromArray(pubKey.mid(0, pubKey.size() / 2));
    INT m = fromArray(pubKey.mid(pubKey.size() / 2));

    short blockSizeOut = getBlockSize(m) + 1; // BlockSize::OneByte
    short blockSizeIn = 1; // BlockSize::OneByte

    if (blockSizeMode == BlockSize::Auto) {
        blockSizeIn = getBlockSize(m);
    }

    if (!blockSizeIn) {
        qDebug() << "module of key small! size = 1 byte, 2 byte is minimum";
        return QByteArray();
    }

    QByteArray res;

    while ((block = rawData.mid(index, blockSizeIn)).size()) {

        if (index + blockSizeIn > rawData.size() && block.size() && !block[0]) {
            qWarning() << "When trying to encrypt data, problems arose, the last block contains non-significant zeros."
                          " These zeros will be deleted during the decryption process."
                          " For encode and decode data with non-significant zeros use BlockSize::OneByte";
        }

        res.append(encodeBlok(fromArray(block), e, m, blockSizeOut));
        index += blockSizeIn;
    }

    return res;

}
QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey, BlockSize blockSizeMode) {

    if (getBitsSize(privKey) != _rsa) {
        return QByteArray();
    }

    int index = 0;

    QByteArray block;

    INT d = fromArray(privKey.mid(0, privKey.size() / 2));
    INT m = fromArray(privKey.mid(privKey.size() / 2));

    short blockSizeIn = getBlockSize(m) + 1;

    short blockSizeOut = 1; // BlockSize::OneByte
    if (blockSizeMode == BlockSize::Auto) {
        blockSizeOut = getBlockSize(m);
    }

    QByteArray res;
    while ((block = rawData.mid(index, blockSizeIn)).size()) {
        bool isLastBlock = (index + blockSizeIn) >= rawData.size();

        res.append(decodeBlok(fromArray(block), d, m,
                              (isLastBlock && blockSizeMode == BlockSize::Auto)? -1 : blockSizeOut));
        index += blockSizeIn;
    }
    return res;

}
QByteArray QRSAEncryption::signMessage(QByteArray rawData, const QByteArray &privKey) {

    QByteArray hash = QCryptographicHash::hash(rawData, HashAlgorithm::Sha256);

    QByteArray signature = encode(hash, privKey, BlockSize::OneByte);

    rawData.append(SIGN_MARKER + signature.toHex() + SIGN_MARKER);

    return rawData;
}
bool QRSAEncryption::checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey) {

    // start position of SIGN_MARKER in rawData
    auto signStartPos = rawData.lastIndexOf(SIGN_MARKER, rawData.length() - signMarkerLength - 1);

    // length of signature in rawData
    auto signLength   = rawData.length() - signStartPos - signMarkerLength * 2;

    // message, that was recieved from channel
    QByteArray message = rawData.left(signStartPos);

    // hash, that was decrypt from recieved signature
    QByteArray recievedHash = decode(QByteArray::fromHex(rawData.mid(signStartPos + signMarkerLength, signLength)),
                                     pubKey, BlockSize::OneByte);

    // if recievedHash == hashAlgorithm(recived message), then signed message is valid
    return recievedHash == QCryptographicHash::hash(message, HashAlgorithm::Sha256);
}

bool QRSAEncryption::save(const QString &file, const QByteArray& key) {
    QFile keyFile(file);

    if (keyFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream stream(&keyFile);
        stream << key.toBase64();

        keyFile.close();
        return true;
    }

    return false;
}

QByteArray QRSAEncryption::load(const QString &file) {
    QFile keyFile(file);

    if (keyFile.open(QIODevice::ReadOnly)) {

        QTextStream stream(&keyFile);

        QByteArray base64DataKey;
        stream >> base64DataKey;

        keyFile.close();
        return QByteArray::fromBase64(base64DataKey);
    }

    return {};
}

QRSAEncryption::Rsa QRSAEncryption::getRsa() const {
    return _rsa;
}

bool QRSAEncryption::testKeyPair(const QByteArray &pubKey, const QByteArray &privKey) {

    QByteArray tesVal = "Test message of encrypkey";

    bool result = tesVal == decode(encode(tesVal, pubKey), privKey);

    if (!result) qWarning() << "(Warning): Testkey Fail, try generate new key pair!";

    return result;
}

// --- end of non-static methods ---

bool QRSAEncryption::isValidRsaKey(const QByteArray &key) {
    return key.size() && ((static_cast<unsigned int>(key.size()) % getKeyBytesSize(RSA_64)) == 0);
}
