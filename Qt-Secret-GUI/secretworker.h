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

public slots:
    void generateKeys(int rsa);

signals:
    void showKeysOnQml();
};

#endif // SECRETWORKER_H
