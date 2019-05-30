#include "qrsaencryption.h"
//#include "BigInt.hpp"

template<class INT>
INT eulerFunc(INT p, INT q) {
    return (p - 1) * (q - 1);
}

template<class INT>
bool isPrime(INT n) {
    if (n < 2) {
        return false;
    }

    for (INT i = 2; (i * i) < n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

template<class INT>
INT randNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int longDiff = 1;
    INT minVal = 0;

    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        longDiff = 2;
        minVal = 0x1000000000000000;
    } /*else if (typeid (INT).hash_code() == typeid (uint128_t).hash_code()) {
        longDiff = 4;
        minVal = "0x10000000000000000000000000000000";

    } else if (typeid (INT).hash_code() == typeid (uint256_t).hash_code()) {
        longDiff = 8;
        minVal = "0x1000000000000000000000000000000000000000000000000000000000000000";
    }*/

    INT res = 1;

    while (longDiff > 0 || minVal > res) {
        longDiff--;
        res *= static_cast<unsigned int>(rand());
    }

    return res;
}

// to du
template<class INT>
INT randPrimeNumber() {
    INT n = 0;
    while (!isPrime(n)) {
       n = randNumber<INT>();
    }

    return n;
}

template<class INT>
bool keyGenerator(QByteArray &pubKey,
                 QByteArray &privKey) {
    INT p = randPrimeNumber<INT>();
    INT q = randPrimeNumber<INT>();

    INT modul = eulerFunc(p, q);

    INT e = randPrimeNumber<INT>();

    INT d = 1 / (e % modul);

    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
       pubKey.append(reinterpret_cast<char*>(&e), sizeof(e));
       pubKey.append(reinterpret_cast<char*>(&modul), sizeof(modul));
       privKey.append(reinterpret_cast<char*>(&d), sizeof(d));
       privKey.append(reinterpret_cast<char*>(&modul), sizeof(modul));

    }

    return false;

}

QRSAEncryption::QRSAEncryption()
{

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
    case RSA_128: {
        if (!keyGenerator<uint64_t>(pubKey, privKey)) {
            return false;
        }
        break;
    }
//    case RSA_256: {
//        using INT = uint128_t;
//        break;
//    }
//    case RSA_512: {
//        using INT = uint256_t;
//        break;
//    }
    default: return false;
    }


    return true;
}


