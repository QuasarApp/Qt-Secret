#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H

#include <QByteArray>
#include <QList>

#define ENDLINE "#_end_#"

class QRSAEncryption
{
public:

    enum Rsa {
        RSA_64 = 64,
        RSA_128 = 128
    };

    QRSAEncryption();

    QByteArray encode(const QByteArray &rawData, const QByteArray &pubKey);
    QByteArray decode(const QByteArray &rawData, const QByteArray &privKey);

    QByteArray signMessage(QByteArray rawData, const QByteArray &privKey);
    bool checkSignMessage(const QByteArray &rawData, const QByteArray &pubKey);

    bool generatePairKey(QByteArray &pubKey, QByteArray &privKey, Rsa = RSA_128);

};

#endif // QRSAENCRYPTION_H
