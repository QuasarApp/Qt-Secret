#include <QByteArray>
#include <qrsaencryption.h>

int main() {


    QRSAEncryption e;

    QByteArray pub, priv;

    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_256);

    return 0;
}
