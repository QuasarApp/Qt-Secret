#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent)
{}

void SecretWorker::generateKeys(int rsa)
{
    QRSAEncryption::generatePairKeyS(pubKey, privKey, QRSAEncryption::Rsa(rsa));
    emit showKeysOnQml();
}

void SecretWorker::encryptMessage(QByteArray pubKey, QByteArray message)
{
    qDebug() << "input message: " << message;
    QRSAEncryption::encodeS(message, pubKey);
    emit showMessageOnQml();
}

void SecretWorker::decryptMessage(QByteArray privKey, QByteArray message)
{
    QRSAEncryption::decodeS(message, privKey);
    emit showMessageOnQml();
}
