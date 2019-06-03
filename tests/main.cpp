#include <QByteArray>
#include <qrsaencryption.h>
#include <QDateTime>
#include <qdebug.h>

int main() {


    QRSAEncryption e;

    QByteArray pub, priv;

    auto t = QDateTime::currentMSecsSinceEpoch();
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_64);

    QByteArray message = "L";

    auto data = e.encode(message, pub);

    auto res = e.decode(data, priv);
    qDebug() << "key generate time RSA_64: " << (QDateTime::currentMSecsSinceEpoch() - t);

    t = QDateTime::currentMSecsSinceEpoch();
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_128);

    qDebug() << "key generate time RSA_128: " << (QDateTime::currentMSecsSinceEpoch() - t);

    auto data2 = e.encode(message, pub);

    auto res2 = e.decode(data2, priv);
    return 0;
}
