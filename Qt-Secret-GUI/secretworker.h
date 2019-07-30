#ifndef SECRETWORKER_H
#define SECRETWORKER_H

#include <QObject>
#include <qrsaencryption.h>

class SecretWorker : public QObject
{
    Q_OBJECT
public:
    explicit SecretWorker(QObject *parent = nullptr);

    QByteArray pubKey;
    QByteArray privKey;

    QByteArray message;

public slots:
    void generateKeys(int rsa);
    void encryptMessage(QByteArray pubKey, QByteArray message);
    void decryptMessage(QByteArray pubKey, QByteArray message);

signals:
    void showKeysOnQml();
    void showMessageOnQml();
};

#endif // SECRETWORKER_H
