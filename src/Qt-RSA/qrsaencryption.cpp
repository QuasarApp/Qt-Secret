//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qrsaencryption.h"

#include <QString>



INT eulerFunc(const INT &p, const INT &q) {
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

INT QRSAEncryption::fromArray(const QByteArray &array) const {
    INT res = 0;
    res.fromHex(array.toHex().toStdString());
    return res;
}

QByteArray QRSAEncryption::toArray(const INT &i, short sizeBlok) {
    QByteArray res;
    auto hex = i.getString(16);
    res = QByteArray::fromHex(QByteArray::fromStdString(i.getString(16)));

    QString resHex = res.toHex();

    if (sizeBlok < 0) {
        return res;
    }

    return res.left(sizeBlok);
}

INT QRSAEncryption::randomNumber() const {
    srand(std::chrono::duration_cast<std::chrono::nanoseconds>
          (std::chrono::system_clock::now().time_since_epoch()).count()
          % std::numeric_limits<int>::max());

    int longDiff = _rsa / (sizeof (int) * 8);

    INT res = 1;

    while (longDiff > 0) {
        longDiff--;
        res *= rand() % std::numeric_limits<int>::max();
    }

    return res;
}

INT QRSAEncryption::toPrime(INT n) const {
    if (!(n % 2)) {
        ++n;
    }

    INT LN = n;
    INT RN = n;

    while (true) {

        if (LN.isPrime()) return LN;

        RN+=2;

        if (LN.isPrime()) return RN;
        LN-=2;
    }
}

INT QRSAEncryption::randomPrimeNumber(INT no) const {
    srand(static_cast<unsigned int>(time(nullptr)));

    // max INT
    INT max('1', _rsa / 2, 2);
    auto str = max.getString();

    auto p = toPrime(randomNumber() % max);
    while(p == no) p = toPrime(randomNumber() % max);

    return p;
}

INT QRSAEncryption::extEuclid(INT a, INT b) const {
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
    return static_cast<short>(i.sizeBytes());
}

QByteArray QRSAEncryption::encodeBlok(const INT &block, const INT &e, const INT &m) {
    return toArray(INT::powm(block, e, m), getBlockSize(m) + 1);
}

QByteArray QRSAEncryption::decodeBlok(const INT &block, const INT &d, const INT &m) {
    return toArray(INT::powm(block, d, m), getBlockSize(m));
}

QRSAEncryption::QRSAEncryption(Rsa rsa) {
    _rsa = rsa;
}

unsigned int QRSAEncryption::getKeyBytesSize(QRSAEncryption::Rsa rsa) {
    return rsa / 4;
}

// --- static methods ---
bool QRSAEncryption::generatePairKeyS(QByteArray &pubKey, QByteArray &privKey,
                                      QRSAEncryption::Rsa rsa) {

    return QRSAEncryption(rsa).generatePairKey(pubKey, privKey);
}
QByteArray QRSAEncryption::encodeS(const QByteArray &rawData, const QByteArray &pubKey) {

    return QRSAEncryption().encode(rawData, pubKey);
}
QByteArray QRSAEncryption::decodeS(const QByteArray &rawData, const QByteArray &privKey) {

    return QRSAEncryption().decode(rawData, privKey);
}
QByteArray QRSAEncryption::signMessageS(QByteArray rawData, const QByteArray &privKey) {

    return QRSAEncryption().signMessage(rawData, privKey);
}
bool QRSAEncryption::checkSignMessageS(const QByteArray &rawData, const QByteArray &pubKey) {

    return QRSAEncryption().checkSignMessage(rawData, pubKey);
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

        d = extEuclid(eilor , e);;

        while(d < 0 ) {
            d += eilor;
        }

        pubKey.append(toArray(e));
        pubKey.append(toArray(modul));
        privKey.append(toArray(d));
        privKey.append(toArray(modul));

    } while (!(keyGenRes = testKeyPair(pubKey, privKey)) && (++cnt < KEY_GEN_LIMIT));

    if(cnt >= KEY_GEN_LIMIT) qWarning() << QString("(Warning): Exceeded limit of key generation (%0)!").arg(KEY_GEN_LIMIT);

    return (keyGenRes && cnt < KEY_GEN_LIMIT);
}

// --- non-static methods ---
QByteArray QRSAEncryption::encode(QByteArray rawData, const QByteArray &pubKey) {

    if (getBitsSize(pubKey) != _rsa) {
        return QByteArray();
    }

    int index = 0;

    QByteArray block;

    INT e = fromArray(pubKey.mid(0, pubKey.size() / 2));
    INT m = fromArray(pubKey.mid(pubKey.size() / 2));
    short blockSize = getBlockSize(m);

    if (!blockSize) {
        qDebug() << "module of key small! size = 1 byte, 2 byte is minimum";
        return QByteArray();
    }

    QByteArray res;

    rawData.append(ENDLINE);

    while ((block = rawData.mid(index, blockSize)).size()) {

        res.append(encodeBlok(fromArray(block), e, m));
        index += blockSize;
    }

    return res;

}
QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey) {

    if (getBitsSize(privKey) != _rsa) {
        return QByteArray();
    }

    int index = 0;

    QByteArray block;

    INT d = fromArray(privKey.mid(0, privKey.size() / 2));
    INT m = fromArray(privKey.mid(privKey.size() / 2));
    short blockSize = getBlockSize(m) + 1;

    QByteArray res;
    while ((block = rawData.mid(index, blockSize)).size()) {
        res.append(decodeBlok(fromArray(block), d, m));
        index += blockSize;
    }
    return res.remove(res.lastIndexOf(ENDLINE), res.size());

}
QByteArray QRSAEncryption::signMessage(QByteArray rawData, const QByteArray &privKey) {

    QByteArray hash = QCryptographicHash::hash(rawData, HashAlgorithm::Sha256);

    QByteArray signature = encode(hash, privKey);

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
                                     pubKey);

    // if recievedHash == hashAlgorithm(recived message), then signed message is valid
    return recievedHash == QCryptographicHash::hash(message, HashAlgorithm::Sha256);
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
