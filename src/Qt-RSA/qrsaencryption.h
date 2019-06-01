#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H

#include <QByteArray>
#include <QList>
#include <uint256_t.h>

class QRSAEncryption
{
public:

    enum Rsa {
        RSA_64 = 64,   // long time of key generate : 1 ms in processor (2.0 KHz)
        RSA_128 = 128, // long time of key generate : 5 s  in processor (2.0 KHz)
        RSA_256 = 256, // long time of key generate : 1 m  in processor (2.0 KHz)
    };

    QRSAEncryption();

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey);
    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey, Rsa = RSA_128);

};

#endif // QRSAENCRYPTION_H
