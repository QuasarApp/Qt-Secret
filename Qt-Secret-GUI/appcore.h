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
    // general to all pages
    void qmlOpenPopup(); // from AppCore to qml
    void qmlClosePopup(); // from AppCore to qml

    // generate keys
    void wrkGenerateKeys(int rsa); // from AppCore to secWorker
    void qmlShowKeys(QByteArray pubKey, QByteArray privKey); // to qml

    // encryption and decryption
    void wrkEncryptMessage(QString pubKey, QString message);
    void wrkDecryptMessage(QString pubKey, QString message);
    void qmlShowMessage(QByteArray message);

    // digital signature
    void printSignedMessage(QByteArray *signedMessage);
    void printSignCheckResult(bool checkResult);

public slots:
    void copyToClipboard(QString text);

    // generate keys
    void generateKeys(int rsa); // from qml to AppCore
    void printKeys(); // from secWorker to from AppCore

    // encryption and decryption
    void getEncryptDecrypt(bool actionType, QString key, QString message); // from qml to AppCore
    void printMessage(); // from secWorker to from AppCore

    // digital signature
    void signMessage(QByteArray *messageToSign);
    void checkSign(QByteArray *messageToCheck);
};

#endif // APPCORE_H
