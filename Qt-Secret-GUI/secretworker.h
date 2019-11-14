#ifndef SECRETWORKER_H
#define SECRETWORKER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <qrsaencryption.h>

#define    NAME_LENGTH     8

class SecretWorker : public QObject
{
    Q_OBJECT
public:
    explicit SecretWorker(QObject *parent = nullptr);

    QString keysDirPath;

    QByteArray pubKey;
    QByteArray privKey;

    QString message;
    bool checkResult;

public slots:
    void generateKeys(int rsa);
    void setKeysDirPath(QString dirPath);
    void saveKeys();

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
