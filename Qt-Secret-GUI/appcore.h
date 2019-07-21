#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <qrsaencryption.h>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = nullptr);

    QByteArray pubKey;
    QByteArray privKey;

signals:
    // generate keys
    void printKeys(QByteArray *pubKey, QByteArray *privKey);
    // encryption and decryption
    void printEncryptedData(QByteArray *encryptedData);
    void printDecryptedData(QByteArray *decryptedData);
    // digital signature
    void printSignedMessage(QByteArray *signedMessage);
    void printSignCheckResult(bool checkResult);

public slots:
    // generate keys
    void generateKeys(QRSAEncryption rsa);
    // encryption and decryption
    void encryptData(QByteArray *dataToEncrypt);
    void decryptData(QByteArray *dataToDecrypt);
    // digital signature
    void signMessage(QByteArray *messageToSign);
    void checkSign(QByteArray *messageToCheck);

private:
    int count;  // Счетчик, которым будем оперировать
};

#endif // APPCORE_H
