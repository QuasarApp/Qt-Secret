#include "qrsaencryption.h"
#include <QFile>
#include <cmath>
#include <QDebug>

template<class INT>
INT eulerFunc(const INT &p, const INT &q) {
    return (p - 1) * (q - 1);
}

template<class INT>
INT mul(const INT &a, const INT &b, const INT &m){
    if(b == 1)
        return a;
    if(b % 2 == 0){
        INT t = mul(a, b / 2, m);
        return (2 * t) % m;
    }
    return (mul(a, b - 1, m) + a) % m;
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
    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        return QRSAEncryption::Rsa::RSA_64;
    } else if (typeid (INT).hash_code() == typeid (uint128_t).hash_code()) {
        return QRSAEncryption::Rsa::RSA_128;

    } else if (typeid (INT).hash_code() == typeid (uint256_t).hash_code()) {
        return QRSAEncryption::Rsa::RSA_256;
    }

    return 0;
}

template<class INT>
INT randNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int longDiff = getBitsSize<INT>() / (sizeof (int) * 8);

    INT res = 1;

    while (longDiff > 0) {
        longDiff--;
        res *= static_cast<unsigned int>(rand());
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

template <class TYPE, class SUBTYPE>
SUBTYPE getPart(const TYPE& i, bool isLeft) {
    if (isLeft) {
        return i.upper();
    }

    return i.lower();
}

template<class INT>
QByteArray toArray(INT i) {
    QByteArray res;
    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        res.append(reinterpret_cast<char*>(&i), sizeof (i));
    } else if (typeid (INT).hash_code() == typeid (uint128_t).hash_code()) {
        res.append(toArray(getPart<uint128_t, uint64_t>(i, true)));
        res.append(toArray(getPart<uint128_t, uint64_t>(i, false)));
    } else if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        res.append(toArray(getPart<uint256_t, uint128_t>(i, true)));
        res.append(toArray(getPart<uint256_t, uint128_t>(i, false)));
    }

    return res;
}


template<class INT>
INT fromArray(const QByteArray& array) {
    if (array.size() == sizeof (uint64_t) && typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        return *(const_cast<INT*>(array.data()));
    } else if (array.size() == (sizeof (uint64_t) * 2) && typeid (INT).hash_code() == typeid (uint128_t).hash_code()) {
        INT res(fromArray<uint64_t>(array.left(array.size() / 2)), fromArray<uint64_t>(array.right(array.size() / 2)));
        return res;
    } else if (array.size() == (sizeof (uint64_t) * 2) && typeid (INT).hash_code() == typeid (uint256_t).hash_code()) {
        INT res(fromArray<uint128_t>(array.left(array.size() / 2)), fromArray<uint128_t>(array.right(array.size() / 2)));
        return res;
    }

    return 0;
}

template<class INT>
bool keyGenerator(QByteArray &pubKey,
                  QByteArray &privKey) {

    INT p = randomPrimeNumber<INT>();
    INT q = (p * 2) + 1;

    INT modul = p * q;
    INT eilor = eulerFunc(p, q);
    INT e = randNumber<INT>() % eilor;

    if (!(e % 2)) e--;

    do {
        e -= 2;

    } while((!isMutuallyPrime(eilor, e)));

    INT d = 0;

    d = ExtEuclid(eilor, e);
    while(d < 0) {
        d += eilor;
    }

    pubKey.append(toArray(e));
    pubKey.append(toArray(modul));
    privKey.append(toArray(d));
    privKey.append(toArray(modul));

    return true;
}

QRSAEncryption::QRSAEncryption() {

}

QByteArray QRSAEncryption::encode(const QByteArray &rawData, const QByteArray &pubKey)
{

}

QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey)
{

}


bool QRSAEncryption::generatePairKey(QByteArray &pubKey,
                                     QByteArray &privKey,
                                     QRSAEncryption::Rsa rsa)
{

    switch (rsa) {
    case RSA_64: {
        if (!keyGenerator<uint64_t>(pubKey, privKey)) {
            return false;
        }
        break;
    }
    case RSA_128: {
        if (!keyGenerator<uint128_t>(pubKey, privKey)) {
            return false;
        }
        break;
    }
    case RSA_256: {

        if (!keyGenerator<uint256_t>(pubKey, privKey)) {
            return false;
        }
        //qDebug() << "RSA_256 not supported. use RSA128 and RSA64";
        //return false;
    }

    }


    return true;
}


