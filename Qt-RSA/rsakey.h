#ifndef RSAKEY_H
#define RSAKEY_H

#include <QString>
#include "../uint256_t/uint256_t.h"

enum class KeyType: short {
    RSA128 = 128,
    RSA256 = 256,
    RSA512 = 512,
    RSA1024 = 1024,
    RSA2048 = 2048,
};

class RsaKey
{
private:
    uint256_t _exp;
//    BigInt _delimiter;
    KeyType _type;

public:
    RsaKey(KeyType type = KeyType::RSA256);
    RsaKey(const QString& hex, KeyType type = KeyType::RSA256);
    QString toHex() const;
    void fromHex(const QString& hex);
    bool isValid() const;
    QByteArray toByteArray() const;
    void fromByteArray(const QByteArray& array);

    friend class QRSAEncryption;
};

#endif // RSAKEY_H
