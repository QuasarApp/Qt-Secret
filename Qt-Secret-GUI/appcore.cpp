#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{

}

void AppCore::generateKeys(int rsaIdx)
{
    QRSAEncryption e((QRSAEncryption::Rsa(rsaIdx)));
    e.generatePairKey(pubKey, privKey);
    emit printKeys(pubKey.toHex(), privKey.toHex());
}

void AppCore::encryptData(QByteArray *dataToEncrypt)
{

}

void AppCore::decryptData(QByteArray *dataToDecrypt)
{

}

void AppCore::signMessage(QByteArray *messageToSign)
{

}

void AppCore::checkSign(QByteArray *messageToCheck)
{

}
