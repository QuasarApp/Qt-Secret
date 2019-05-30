#include <QByteArray>
#include "Qt-RSA/qrsaencryption.h"

int main(int argc, char** argv) {


    QRSAEncryption e;

    QByteArray pub, priv;

    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_256);

    return 0;
}
