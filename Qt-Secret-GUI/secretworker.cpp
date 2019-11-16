#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent)
{}

void SecretWorker::generateKeys(int rsa) {

    QRSAEncryption::generatePairKey(pubKey, privKey, QRSAEncryption::Rsa(rsa));
    emit showKeysOnQml();
}

void SecretWorker::encryptMessage(QString encPubKey, QString inputText) {

    message = QString(QRSAEncryption::encode(inputText.toUtf8(),
                                              QByteArray::fromHex(encPubKey.toUtf8()),
                                              QRSAEncryption::Rsa(encPubKey.length() * 2)).toHex());
    emit showEncDecResOnQml();
}

void SecretWorker::decryptMessage(QString decPrivKey, QString inputMessage) {

    message = QString(QRSAEncryption::decode(QByteArray::fromHex(inputMessage.toUtf8()),
                                              QByteArray::fromHex(decPrivKey.toUtf8()),
                                              QRSAEncryption::Rsa(decPrivKey.length() * 2)));
    emit showEncDecResOnQml();
}

void SecretWorker::signMessage(QString signPrivKey, QString inputMessage) {

    message = QString(QRSAEncryption::signMessage(inputMessage.toUtf8(),
                                                   QByteArray::fromHex(signPrivKey.toUtf8()),
                                                   QRSAEncryption::Rsa(signPrivKey.length() * 2)));
    emit showSignResOnQml();
}

void SecretWorker::checkSign(QString signPubKey, QString inputMessage) {

    message = QRSAEncryption::checkSignMessage(inputMessage.toUtf8(),
                                                QByteArray::fromHex(signPubKey.toUtf8()),
                                                QRSAEncryption::Rsa(signPubKey.length() * 2)) ? "Sign is true" : "Sign is false";
    emit showSignResOnQml();
}
