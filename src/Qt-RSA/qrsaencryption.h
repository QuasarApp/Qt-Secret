//#
//# Copyright (C) 2018-2020 QuasarApp.
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

/**
 * @brief The QRSAEncryption class Fast encryption class for RSA algorithm.
 */
class Qt_SECRETSHARED_EXPORT QRSAEncryption
{
public:
    typedef BigInt INT;
    typedef QCryptographicHash::Algorithm HashAlgorithm;

    /**
     * @brief The Rsa enum Determines the size of the secret and public keys expanents (bits).
To ensure reliable protection, it is recommended to use an exponent size of at least 2048 bits.
     */
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

    /**
     * @brief The BlockSize enum defined size of block of key
     * Auto - fast but not stable. (using by default)
     * OneByte - // stable but slow. (using for sig and check sig messages)
     */
    enum BlockSize {
        Auto = 0, // fast but not stable. (using by default)
        OneByte = 1 // stable but slow. (using for sig and check sig messages)
    };


    /**
     * @brief QRSAEncryption
     * @param rsa - the Rsa size of class.
     */
    QRSAEncryption(Rsa rsa = Rsa::RSA_256);

// static methods

    /**
     * @brief generatePairKey staic implementation of generatePairKey
     * @param pubKey
     * @param privKey
     * @param rsa
     * @return
     */
    static bool generatePairKey(QByteArray &pubKey, QByteArray &privKey,
                                 QRSAEncryption::Rsa rsa);

    /**
     * @brief encode - static implementation of encode
     * @param rawData
     * @param pubKey
     * @param rsa
     * @param blockSizeMode
     * @return
     */
    static QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey,
                              Rsa rsa, BlockSize blockSizeMode = BlockSize::Auto);

    /**
     * @brief decode static implementation of decode
     * @param rawData
     * @param privKey
     * @param rsa
     * @param blockSizeMode
     * @return
     */
    static QByteArray decode(const QByteArray &rawData, const QByteArray &privKey,
                              Rsa rsa, BlockSize blockSizeMode = BlockSize::Auto);

    /**
     * @brief signMessage - static implementation of signMessage
     * @param rawData
     * @param privKey
     * @param rsa
     * @return
     */
    static QByteArray signMessage(QByteArray rawData, const QByteArray &privKey,
                                   Rsa rsa);

    /**
     * @brief checkSignMessage static implementation of checkSignMessage
     * @param rawData
     * @param pubKey
     * @param rsa
     * @return
     */
    static bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey,
                                  Rsa rsa);

    /**
     * @brief isValidRsaKey Сhecks byte array. If the array is the PCA key, it will return true, in the practical case of false.
     * @param key - the validation key
     * @return true if key is RSA
     */
    static bool isValidRsaKey(const QByteArray& key);

    /**
     * @brief getKeyBytesSize Return keySize of bits
     * @param rsa - the rsa key
     * @return return size of key
     */
    static unsigned int getKeyBytesSize(QRSAEncryption::Rsa rsa);

    /**
     * @brief getKeyRsaType - return the key RSA type.
     * @param key - public or private RSA key.
     * @return QRSAEncryption::Rsa
     */
    static QRSAEncryption::Rsa getKeyRsaType(const QByteArray& key);

    /**
     * @brief save - save key into file.
     * @param file
     * @param key
     * @return true if all good.
     */
    static bool save(const QString& file, const QByteArray &key);

    /**
     * @brief load - read key from file
     * @param file
     * @return Key if all good. If key read fail return empty array.
     */
    static QByteArray load(const QString& file);

// non-static methods

    /**
     * @brief generatePairKey - generate RSA pair keys
     * @param pubKey - return value of pablic key
     * @param privKey - return value of private key
     * @return true if all good.
     */
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey);

    /**
     * @brief encode - encode rawData
     * @param rawData - data for encode
     * @param pubKey - public key. Public key size must be equals size of RSA class.
     * @param blockSizeMode - block size. See @BlockSize
     * @return The encoded data.
     */
    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey,
                      BlockSize blockSizeMode = BlockSize::Auto);

    /**
     * @brief decode - decode raw encoded data.
     * it is important that the data is decrypted and encrypted by the same class, or in the case of static methods with the same parameters
     * @param rawData - ecoded data.
     * @param privKey - private RSA key
     * @param blockSizeMode - block size mode see @BlockSize
     * @return decoded data
     */
    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey,
                      BlockSize blockSizeMode = BlockSize::Auto);

    /**
     * @brief signMessage
     * @param rawData - the raw data for signature
     * @param privKey - the private key
     * @return the signed message.
     */
    QByteArray signMessage(QByteArray rawData, const QByteArray &privKey);

    /**
     * @brief checkSignMessage - verify signed raw data with a public key.
     * @param rawData - the raw data for verification
     * @param pubKey - the public key
     * @return true if data sigend.
     */
    bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey);

    /**
     * @brief getRsa
     * @return the Rsa type of class
     */
    Rsa getRsa() const;

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
