#ifndef SECRETWORKER_H
#define SECRETWORKER_H

#include <QObject>
#include <QDebug>
#include <qrsaencryption.h>

class SecretWorker : public QObject
{
    Q_OBJECT
public:
    explicit SecretWorker(QObject *parent = nullptr);

    QByteArray pubKey;
    QByteArray privKey;

    QString message;

public slots:
    void generateKeys(int rsa);

    void encryptMessage(QString encPubKey,  QString inputText);
    void decryptMessage(QString decPrivKey, QString inputMessage);

signals:
    void showKeysOnQml();
    void showMessageOnQml();
};

#endif // SECRETWORKER_H
