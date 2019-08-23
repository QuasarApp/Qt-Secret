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
    bool checkResult;

public slots:
    void generateKeys(int rsa);

    void encryptMessage(QString encPubKey,  QString inputText);
    void decryptMessage(QString decPrivKey, QString inputMessage);

    void signMessage(QString signPrivKey, QString inputMessage);
    void checkSign(QString signPubKey, QString inputMessage);

signals:
    void showKeysOnQml();
    void showEncDecResOnQml();
    void showSignResOnQml();
};

#endif // SECRETWORKER_H
