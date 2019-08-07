#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent)
{}

void SecretWorker::generateKeys(int rsa)
{
    QRSAEncryption::generatePairKeyS(pubKey, privKey, QRSAEncryption::Rsa(rsa));
    emit showKeysOnQml();
}

void SecretWorker::encryptMessage(QString encPubKey, QString inputText)
{
    message = QRSAEncryption::encodeS(inputText.toUtf8(), encPubKey.toUtf8(), QRSAEncryption::Rsa(encPubKey.length() * 4));
    emit showMessageOnQml();
}

void SecretWorker::decryptMessage(QString decPrivKey, QString inputMessage)
{
    message = QRSAEncryption::decodeS(inputMessage.toUtf8(), decPrivKey.toUtf8(), QRSAEncryption::Rsa(decPrivKey.length() * 4));
    emit showMessageOnQml();
}
