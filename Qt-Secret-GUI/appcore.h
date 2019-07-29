#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QThread>
#include <QClipboard>
#include <secretworker.h>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = nullptr, QClipboard *clpbrd = nullptr);
    ~AppCore();

    SecretWorker secWorker;
    QThread workThread;

    QClipboard *clipboard;

signals:
    // generate keys
    void wrkGenerateKeys(int rsa); // from AppCore to secWorker
    void qmlOpenPopup(); // from AppCore to qml
    void qmlShowKeys(QByteArray pubKey, QByteArray privKey); // to qml

    // encryption and decryption
    void printEncryptedData(QByteArray *encryptedData);
    void printDecryptedData(QByteArray *decryptedData);

    // digital signature
    void printSignedMessage(QByteArray *signedMessage);
    void printSignCheckResult(bool checkResult);

public slots:
    // generate keys
    void generateKeys(int rsa); // from qml to from AppCore
    void printKeys(); // from secWorker to from AppCore
    void copyToClipboard(QString text);

    // encryption and decryption
    void encryptData(QByteArray *dataToEncrypt);
    void decryptData(QByteArray *dataToDecrypt);

    // digital signature
    void signMessage(QByteArray *messageToSign);
    void checkSign(QByteArray *messageToCheck);
};

#endif // APPCORE_H
