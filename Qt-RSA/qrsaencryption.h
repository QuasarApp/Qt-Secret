#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H

#include <QByteArray>
#include "../uint256_t/uint256_t.h"

class QRSAEncryption
{
public:
    enum Rsa {
        RSA_128 = 128,
        RSA_256 = 256,
        RSA_512 = 512
    };

    enum RsaKeyType {
        Public,
        Private
    };

    QRSAEncryption();

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &pubKey);
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey, Rsa = RSA_128);

};

#endif // QRSAENCRYPTION_H
