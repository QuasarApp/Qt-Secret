#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent)
{}

void SecretWorker::generateKeys(int rsa)
{
    QRSAEncryption::generatePairKeyS(pubKey, privKey, QRSAEncryption::Rsa(rsa));
    emit showKeysOnQml();
}
