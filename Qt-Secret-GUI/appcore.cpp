#include "appcore.h"

AppCore::AppCore(QObject *parent, QClipboard *clpbrd) : QObject(parent) {

    clipboard = clpbrd;

    connect(this, &AppCore::wrkGenerateKeys, &secWorker, &SecretWorker::generateKeys);
    connect(&secWorker, &SecretWorker::showKeysOnQml, this, &AppCore::printKeys);

    connect(this, &AppCore::wrkEncryptMessage, &secWorker, &SecretWorker::encryptMessage);
    connect(this, &AppCore::wrkDecryptMessage, &secWorker, &SecretWorker::decryptMessage);
    connect(&secWorker, &SecretWorker::showMessageOnQml, this, &AppCore::printMessage);

    secWorker.moveToThread(&workThread);
    workThread.start();
}

AppCore::~AppCore() {

    workThread.quit();
    workThread.wait();
}

void AppCore::generateKeys(int rsa) {
    emit qmlOpenPopup();
    emit wrkGenerateKeys(rsa);
}

void AppCore::printKeys() {
    emit qmlShowKeys(secWorker.pubKey.toHex(), secWorker.privKey.toHex());
    emit qmlClosePopup();
}

void AppCore::copyToClipboard(QString text) {
    clipboard->setText(text);
}

void AppCore::getEncryptDecrypt(bool actionType, QString key, QString message)
{
    // encryption
    if(actionType) {
        emit qmlOpenPopup();
        emit wrkEncryptMessage(key.toUtf8(), message.toUtf8());
    }
    // decryption
    else {
        emit qmlOpenPopup();
        emit wrkDecryptMessage(key.toUtf8(), message.toUtf8());
    }
}

void AppCore::printMessage()
{
    qDebug() << "print message: " << secWorker.message.toHex();
    emit qmlShowMessage(secWorker.message.toHex());
    emit qmlClosePopup();
}

void AppCore::signMessage(QByteArray *messageToSign) {

}

void AppCore::checkSign(QByteArray *messageToCheck) {

}
