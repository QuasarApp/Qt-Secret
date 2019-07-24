#include "appcore.h"

AppCore::AppCore(QObject *parent, QClipboard *_clipboard) : QObject(parent)
{
    clipboard = _clipboard;

    connect(this, &AppCore::wrkGenerateKeys, &secWorker, &SecretWorker::generateKeys);
    connect(&secWorker, &SecretWorker::showKeysOnQml, this, &AppCore::printKeys);

    secWorker.moveToThread(&workThread);
    workThread.start();
}

AppCore::~AppCore()
{
    workThread.wait(0);
    workThread.quit();
}

void AppCore::generateKeys(int rsa)
{
    emit qmlOpenPopup();
    emit wrkGenerateKeys(rsa);
}

void AppCore::printKeys()
{
    emit qmlShowKeys(secWorker.pubKey.toHex(), secWorker.privKey.toHex());
}

void AppCore::copyToClipboard(QString text)
{
    clipboard->setText(text);
}

void AppCore::encryptData(QByteArray *dataToEncrypt)
{}

void AppCore::decryptData(QByteArray *dataToDecrypt)
{}

void AppCore::signMessage(QByteArray *messageToSign)
{}

void AppCore::checkSign(QByteArray *messageToCheck)
{}
