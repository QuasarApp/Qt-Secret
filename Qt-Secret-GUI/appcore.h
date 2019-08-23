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
    void wrkDecryptMessage(QString privKey, QString message);
    void qmlShowEncDecResult(QString message);

    // digital signature
    void wrkSignMessage(QString privKey, QString message);
    void wrkCheckSign(QString pubKey, QString message);
    void qmlShowSignResult(QString message);

public slots:
    void copyToClipboard(QString text);

    // generate keys
    void generateKeys(int rsa);
    void printKeys();

    // encryption and decryption
    void getEncryptDecrypt(bool actionType, QString key, QString message);
    void printEncDecResult();

    // sign message and check sign
    void getSignCheck(bool actionType, QString key, QString message);
    void printSignResult();
};

#endif // APPCORE_H
