#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent)
{}

void SecretWorker::generateKeys(int rsa)
{
    QRSAEncryption::generatePairKeyS(pubKey, privKey, QRSAEncryption::Rsa(rsa));
    emit showKeysOnQml();
}

void SecretWorker::encryptMessage(QByteArray pubKey, QByteArray inputText)
{
    message = QRSAEncryption::encodeS(inputText, pubKey);
    emit showMessageOnQml();
}

void SecretWorker::decryptMessage(QByteArray privKey, QByteArray inputMessage)
{
    message = QRSAEncryption::decodeS(inputMessage, privKey);
    emit showMessageOnQml();
}
