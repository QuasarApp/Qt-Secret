#ifndef QRSAENCRYPTION_H
#define QRSAENCRYPTION_H


class QRSAEncryption
{
public:
    QRSAEncryption();
    static QByteArray ExpandKey(QAESEncryption::Aes level, QAESEncryption::Mode mode, const QByteArray &key);

    QByteArray encode(const QByteArray &rawText, const QByteArray &key, const QByteArray &iv = NULL);
    QByteArray decode(const QByteArray &rawText, const QByteArray &key, const QByteArray &iv = NULL);

};

#endif // QRSAENCRYPTION_H
