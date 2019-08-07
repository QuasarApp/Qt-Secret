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
    message = QString(QRSAEncryption::encodeS(inputText.toUtf8(),
                                              QByteArray::fromHex(encPubKey.toUtf8()),
                                              QRSAEncryption::Rsa(encPubKey.length() * 2)).toHex());
    emit showMessageOnQml();
}

void SecretWorker::decryptMessage(QString decPrivKey, QString inputMessage)
{
    message = QString(QRSAEncryption::decodeS(QByteArray::fromHex(inputMessage.toUtf8()),
                                              QByteArray::fromHex(decPrivKey.toUtf8()),
                                              QRSAEncryption::Rsa(decPrivKey.length() * 2)));
    emit showMessageOnQml();
}
