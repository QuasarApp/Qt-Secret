//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qrsaencryption.h"
#include <QFile>
#include <cmath>
#include <QDebug>

typedef unsigned __int128  uint128_t;
typedef signed __int128  int128_t;

template<class INT>
INT eulerFunc(const INT &p, const INT &q) {
    return (p - 1) * (q - 1);
}

template<class INT>
INT mul(INT a, INT b, const INT &m) {
    INT res = 0;
    while (a != 0) {
        if (a & 1) res = (res + b) % m;
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}

template<class INT>
INT pows(const INT &a, const INT &b, const INT &m) {
    if(b == 0)
        return 1;
    if(b % 2 == 0){
        INT t = pows(a, b / 2, m);
        return mul(t , t, m) % m;
    }
    return ( mul(pows(a, b - 1, m) , a, m)) % m;
}

template<class INT>
INT binpow (INT a, INT n, INT m) {
    INT res = 1;
    while (n) {
        if (n & 1) {
            res = mul(res, a, m);
        }
        a = mul(a, a % m, m);
        n >>= 1;
    }
    return res % m;
}

template<class INT>
bool gcd(INT a, INT b) {
    INT c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

template<class INT>
bool isMutuallyPrime(INT a, INT b) {
    if ((!(a % 2) && !(b % 2)) || (!(a % 3) && !(b % 3)) || (!(a % 5) && !(b % 5)) || (!(a % 7)  && !(b % 7))) {
        return false;
    }

    return gcd(a, b) == 1;
}

template<class INT>
unsigned int getBitsSize() {
    return sizeof(INT) * 8;
}

template<class INT>
INT randNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int longDiff = getBitsSize<INT>() / (sizeof (int) * 8);

    INT res = 1;

    while (longDiff > 0) {
        longDiff--;
        res *= rand() % std::numeric_limits<int>::max();
    }

    return res;
}

template<class INT>
bool isPrimeFerma(INT x){
    if(x == 2)
        return true;

    for(int i = 0; i < 100; i++){
        INT a = (randNumber<INT>() % (x - 2)) + 2;
        if (!isMutuallyPrime(a, x))
            return false;
        if( pows(a, x-1, x) != 1)
            return false;
    }

    return true;
}

template<class INT>
INT toPrime(INT n) {

    if (!(n % 2)) {
        n++;
    }

    INT LN = n;
    INT RN = n;

    while (true) {
        if (isPrimeFerma(LN)) {
            return LN;
        }

        RN+=2;

        if (isPrimeFerma(RN)) {
            return RN;
        }

        LN-=2;
    }
}

template<class INT>
INT randomPrimeNumber(INT no = 0) {
    srand(static_cast<unsigned int>(time(nullptr)));

    auto p = toPrime(randNumber<INT>() >> (getBitsSize<INT>() / 2));
    while(p == no) p = toPrime(randNumber<INT>() >> (getBitsSize<INT>() / 2));

    return p;
}

template<class INT>
INT ExtEuclid(INT a, INT b)
{
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


template<class INT>
QByteArray toArray(INT i, short sizeBlok = -1) {
    QByteArray res;
    res.append(reinterpret_cast<char*>(&i), sizeof (i));

    if (sizeBlok < 0) {
        return res;
    }

    //    while (res.rbegin() != res.rend() && !*res.rbegin()) {
    //        res.remove(res.size() -1, 1);
    //    }

    return res.left(sizeBlok);
}

template<class INT>
INT fromArray(const QByteArray& array) {
    INT res = 0;

    memcpy(&res, array.data(),
           static_cast<unsigned int>(std::min(array.size(),
                                              static_cast<int>(sizeof(INT)))));
    return res;
}

template<class INT>
bool keyGenerator(QByteArray &pubKey,
                  QByteArray &privKey) {

    INT p = randomPrimeNumber<INT>();
    INT q = randomPrimeNumber<INT>(p);

    INT modul = 0;
    while ((modul = p * q) < 0) {
        p = toPrime((p - 1) / 2);
    }

    INT eilor = eulerFunc(p, q);
    INT e = randNumber<INT>() % eilor;

    if (!(e % 2)) e--;

    do {
        e -= 2;

    } while((!isMutuallyPrime(eilor, e)));

    INT d = ExtEuclid<INT>(eilor , e);;

    while(d < 0 ) {
        d += eilor;
    }

    pubKey.append(toArray(e));
    pubKey.append(toArray(modul));
    privKey.append(toArray(d));
    privKey.append(toArray(modul));

    return true;
}

template< class INT>
short getBytes(INT i) {
    return static_cast<short>(std::floor(log2(i) / 8)) ;
}

template<class INT>
short getBlockSize(const INT &i) {
    return getBytes<INT>(i);
}

template <class INT>
QByteArray encodeBlok(const INT& block, const INT &e, const INT &m) {
    return toArray(binpow(block, e, m), getBlockSize(m) + 1);
}

template <class INT>
QByteArray decodeBlok(const INT& block, const INT &d, const INT &m) {
    return toArray(binpow(block, d, m), getBlockSize(m));
}

template<class INT>
QByteArray encodeArray(QByteArray rawData, const QByteArray &pubKey) {
    int index = 0;

    QByteArray block;

    INT e = fromArray<INT>(pubKey.mid(0, pubKey.size() / 2));
    INT m = fromArray<INT>(pubKey.mid(pubKey.size() / 2));
    short blockSize = getBlockSize(m);

    if (!blockSize) {
        qDebug() << "module of key small! size = 1 byte, 2 byte is minimum";
        return QByteArray();
    }

    QByteArray res;

    rawData.append(ENDLINE);

    while ((block = rawData.mid(index, blockSize)).size()) {

        res.append(encodeBlok(fromArray<INT>(block), e, m));
        index += blockSize;
    }

    return res;
}


template<class INT>
QByteArray decodeArray(const QByteArray &rawData, const QByteArray &privKey) {
    int index = 0;

    QByteArray block;

    INT d = fromArray<INT>(privKey.mid(0, privKey.size() / 2));
    INT m = fromArray<INT>(privKey.mid(privKey.size() / 2));
    short blockSize = getBlockSize(m) + 1;

    QByteArray res;
    while ((block = rawData.mid(index, blockSize)).size()) {
        res.append(decodeBlok(fromArray<INT>(block), d, m));
        index += blockSize;
    }
    return res.remove(res.lastIndexOf(ENDLINE), res.size());
}

bool QRSAEncryption::testKeyPair(const QByteArray &pubKey, const QByteArray &privKey) {
    QByteArray tesVal = "Test message of encrypkey";
    bool result = tesVal == decode(encode(tesVal, pubKey), privKey);

    if (!result) {
        qWarning() << "(Warning): Testkey Fail, try generate new key pair!";
    }

    return result;
}

QRSAEncryption::QRSAEncryption() {

}

QByteArray QRSAEncryption::encode(const QByteArray &rawData, const QByteArray &pubKey) {

    switch (pubKey.size()) {
    case RSA_64 / 4: {
        return encodeArray<uint64_t>(rawData, pubKey);
    }

    case RSA_128 / 4: {
        return encodeArray<uint128_t>(rawData, pubKey);
    }

    default: return QByteArray();
    }
}


QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey) {

    switch (privKey.size()) {
    case RSA_64 / 4: {
        return decodeArray<uint64_t>(rawData, privKey);
    }

    case RSA_128 / 4: {
        return decodeArray<uint128_t>(rawData, privKey);
    }

    default: return QByteArray();
    }
}

QByteArray QRSAEncryption::signMessage(QByteArray rawData, const QByteArray &privKey) {
    auto msg = encode(rawData, privKey);
    int size = rawData.size();
    rawData.insert(0, reinterpret_cast<char*>(&size), sizeof (int));
    rawData.append(msg);

    return rawData;
}

bool QRSAEncryption::checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey) {
    int mSize = 0;
    memcpy(&mSize, rawData.left(sizeof (int)), sizeof (int));

    auto message = rawData.mid(sizeof (int), mSize);
    auto sig = rawData.mid(mSize + static_cast<int>(sizeof (int)));

    return message == decode(sig, pubKey);
}

bool QRSAEncryption::generatePairKey(QByteArray &pubKey,
                                     QByteArray &privKey,
                                     QRSAEncryption::Rsa rsa) {

    qDebug() << "from forked" << endl;

    do {

        pubKey.clear();
        privKey.clear();

        switch (rsa) {
        case RSA_64: {

            if (!keyGenerator<int64_t>(pubKey, privKey)) {
                return false;
            }


            break;
        }
        case RSA_128: {
            if (!keyGenerator<int128_t>(pubKey, privKey)) {
                return false;
            }
            break;
        }

        }

    } while (!testKeyPair(pubKey, privKey));


    return true;
}


