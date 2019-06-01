#include <QByteArray>
#include <qrsaencryption.h>
#include <QDateTime>
#include <qdebug.h>

int main() {


    QRSAEncryption e;

    QByteArray pub, priv;

    auto t = QDateTime::currentMSecsSinceEpoch();
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_64);

    qDebug() << "key generate time RSA_64: " << (QDateTime::currentMSecsSinceEpoch() - t);

    t = QDateTime::currentMSecsSinceEpoch();
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_128);

    qDebug() << "key generate time RSA_128: " << (QDateTime::currentMSecsSinceEpoch() - t);

    t = QDateTime::currentMSecsSinceEpoch();
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_256);

    qDebug() << "key generate time RSA_256: " << (QDateTime::currentMSecsSinceEpoch() - t);

    return 0;
}
