#include "appcore.h"

AppCore::AppCore(QObject *parent, QClipboard *clpbrd) : QObject(parent) {

    clipboard = clpbrd;

    connect(this, &AppCore::wrkGenerateKeys, &secWorker, &SecretWorker::generateKeys);
    connect(&secWorker, &SecretWorker::showKeysOnQml, this, &AppCore::printKeys);

    connect(this, &AppCore::wrkEncryptMessage, &secWorker, &SecretWorker::encryptMessage);
    connect(this, &AppCore::wrkDecryptMessage, &secWorker, &SecretWorker::decryptMessage);
    connect(&secWorker, &SecretWorker::showEncDecResOnQml, this, &AppCore::printEncDecResult);

    connect(this, &AppCore::wrkSignMessage, &secWorker, &SecretWorker::signMessage);
    connect(this, &AppCore::wrkCheckSign, &secWorker, &SecretWorker::checkSign);
    connect(&secWorker, &SecretWorker::showSignResOnQml, this, &AppCore::printSignResult);

    secWorker.moveToThread(&workThread);
    workThread.start();
}

AppCore::~AppCore() {

    workThread.quit();
    workThread.wait();
}

void AppCore::copyToClipboard(QString text) {

    clipboard->setText(text);
}

// generate keys
void AppCore::generateKeys(int rsa) {

    emit qmlOpenPopup();
    emit wrkGenerateKeys(rsa);
}

void AppCore::printKeys() {

    emit qmlShowKeys(secWorker.pubKey.toHex(), secWorker.privKey.toHex());
    emit qmlClosePopup();
}

// encryption and decryption
void AppCore::getEncryptDecrypt(bool actionType, QString key, QString message) {

    emit qmlOpenPopup();

    // encryption
    if(actionType) {
        emit wrkEncryptMessage(key, message);
    }
    // decryption
    else {
        emit wrkDecryptMessage(key, message);
    }
}

void AppCore::printEncDecResult() {

    emit qmlShowEncDecResult(secWorker.message);
    emit qmlClosePopup();
}

// sign message and check sign
void AppCore::getSignCheck(bool actionType, QString key, QString message) {

    emit qmlOpenPopup();

    // sign message
    if(actionType) {
        emit wrkSignMessage(key, message);
    }
    // check sign
    else {
        emit wrkCheckSign(key, message);
    }
}

void AppCore::printSignResult() {

    emit qmlShowSignResult(secWorker.message);
    emit qmlClosePopup();
}
