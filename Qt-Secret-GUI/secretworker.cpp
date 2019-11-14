#include "secretworker.h"

SecretWorker::SecretWorker(QObject *parent) : QObject(parent) {
    keysDirPath = QDir::toNativeSeparators(QDir::homePath()) + "/.Qt-Secret-GUI";
    QDir().mkpath(keysDirPath);
}

void SecretWorker::generateKeys(int rsa) {

    QRSAEncryption::generatePairKeyS(pubKey, privKey, QRSAEncryption::Rsa(rsa));

    saveKeys();

    emit showKeysOnQml();
}

void SecretWorker::setKeysDirPath(QString dirPath) {
    if(QDir(dirPath).exists()) {
        keysDirPath = dirPath;
    }
}

void SecretWorker::saveKeys() {
    if(pubKey.toHex().right(NAME_LENGTH) == privKey.toHex().right(NAME_LENGTH)) {
        QString keyBaseName = pubKey.toHex().right(NAME_LENGTH);
        QFile outFile;

        outFile.setFileName(keysDirPath + "/" + keyBaseName + ".pub");
        if(outFile.open(QIODevice::ReadWrite)) {
            outFile.write("-----BEGIN PUBLIC KEY-----\n");
            outFile.write(pubKey.toHex().toBase64(QByteArray::Base64Encoding));
            outFile.write("\n-----END PUBLIC KEY-----");
            outFile.close();
        }

        outFile.setFileName(keysDirPath + "/" + keyBaseName + ".priv");
        if(outFile.open(QIODevice::ReadWrite)) {
            outFile.write("-----BEGIN PRIVATE KEY-----\n");
            outFile.write(privKey.toHex().toBase64(QByteArray::Base64Encoding));
            outFile.write("\n-----END PRIVATE KEY-----");
            outFile.close();
        }
    } else {
        qDebug() << "error in keys";
    }
}

void SecretWorker::encryptMessage(QString encPubKey, QString inputText) {

    message = QString(QRSAEncryption::encodeS(inputText.toUtf8(),
                                              QByteArray::fromHex(encPubKey.toUtf8()),
                                              QRSAEncryption::Rsa(encPubKey.length() * 2)).toHex());
    emit showEncDecResOnQml();
}

void SecretWorker::decryptMessage(QString decPrivKey, QString inputMessage) {

    message = QString(QRSAEncryption::decodeS(QByteArray::fromHex(inputMessage.toUtf8()),
                                              QByteArray::fromHex(decPrivKey.toUtf8()),
                                              QRSAEncryption::Rsa(decPrivKey.length() * 2)));
    emit showEncDecResOnQml();
}

void SecretWorker::signMessage(QString signPrivKey, QString inputMessage) {

    message = QString(QRSAEncryption::signMessageS(inputMessage.toUtf8(),
                                                   QByteArray::fromHex(signPrivKey.toUtf8()),
                                                   QRSAEncryption::Rsa(signPrivKey.length() * 2)));
    emit showSignResOnQml();
}

void SecretWorker::checkSign(QString signPubKey, QString inputMessage) {

    message = QRSAEncryption::checkSignMessageS(inputMessage.toUtf8(),
                                                QByteArray::fromHex(signPubKey.toUtf8()),
                                                QRSAEncryption::Rsa(signPubKey.length() * 2)) ? "Sign is true" : "Sign is false";
    emit showSignResOnQml();
}
