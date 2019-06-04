#include <QByteArray>
#include <qrsaencryption.h>
#include <QDateTime>
#include <qdebug.h>
#include <cmath>

QByteArray randomArray() {
    srand(static_cast<unsigned int>(time(nullptr)));
    QByteArray res;

    int length = rand() % 1024 * 1024;

    for (int i = 0; i < length; ++i) {
        res.push_back(static_cast<char>(rand() % 0xFF));
    }

    return res;
}

bool testCrypto(QRSAEncryption::Rsa rsa) {
    QByteArray pub, priv;
    QRSAEncryption e;


    for (int i = 0; i < 100; i++) {
        e.generatePairKey(pub, priv, rsa);

        if (pub.size() != rsa / 4) {
            qCritical() << "pubKey size wrong RSA" << rsa;
            return false;
        }


        if (priv.size() != rsa / 4) {
            qCritical() << "privKey size wrong RSA" << rsa;
            return false;
        }

        for (int i = 0; i < 100; i++) {
            auto base = randomArray();

            if ( base != e.decode(e.encode(base, pub), priv)) {
                qCritical() << "encode decode data error RSA" << rsa;
                return false;
            }

            if (!e.checkSignMessage(e.signMessage(base, pub), priv)) {
                qCritical() << "sig message error RSA" << rsa;
                return false;
            }

        }
    }

    return true;
}


int main() {

    if(!testCrypto(QRSAEncryption::Rsa::RSA_64)) {
        return 1;
    }

    if(!testCrypto(QRSAEncryption::Rsa::RSA_128)) {
        return 1;
    }

    qInfo() << "Tests passed successfully";

    return 0;
}
