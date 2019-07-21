#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{

}

void AppCore::generateKeys(QRSAEncryption rsa)
{
    QRSAEncryption e(rsa);
    e.generatePairKey(pubKey, privKey);
    emit printKeys(&pubKey, &privKey);
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
