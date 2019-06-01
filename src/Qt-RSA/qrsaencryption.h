#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H

#include <QByteArray>
#include <QList>
#include <uint256_t.h>

class QRSAEncryption
{
public:
    enum Rsa {
        RSA_64 = 64,
        RSA_128 = 128,
        RSA_256 = 256,
    };

    QRSAEncryption();

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &pubKey);
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey, Rsa = RSA_128);

};

#endif // QRSAENCRYPTION_H
