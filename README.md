# ![Qt-Secret Logo](res/png/QtSecretLogo2.png)

Fast encryption library supporting RSA and AES algorithms.

# Futures 
The Qt-Secret library supports the following algorithms:

### RSA
The current implementation supports the following key sizes:
#### Supported sizes
 * RSA64 
 * RSA128 
 * RSA256
 * RSA512
 * RSA1024 
 * RSA2048
 * RSA4096 
 * RSA8192 

#### Supported futures 

* Encryption and decryption of messages.
* Signature and verification of the message signature.

### AES
Aes implementation was borrowed from [bricke](https://github.com/bricke/Qt-AES), because it fulfills the goals of this library.

Individual thanks [bricke](https://github.com/bricke) for implementing the AES encryption class.

#### AES Levels
The class supports all AES key lenghts

* AES_128
* AES_192
* AES_256

#### Modes
The class supports the following operating modes

* ECB
* CBC
* CFB
* OFB

#### Padding
By default the padding method is `ISO`, however, the class supports:

* ZERO
* PKCS7
* ISO


# Build

 * git clone https://github.com/QuasarApp/Qt-Secret.git
 * cd Qt-Secret
 * git submodule update --init --recursive
 * sudo apt install qt5-default
 * qmake -r DEFINE+=WITHOUT_GUI Qt-Secret.pro 
  > DEFINE+=WITHOUT_GUI fot build without gui example, if you want build gui example remove this line. For build the gui example you need to install qml controls 2 in you os. Try **sudo apt install qml-module-qtquick-controls2 qtdeclarative5-dev qtdeclarative5-qtquick2-plugin**
 * make -j8
 * make test #(for testing)

# Include

## for qmake projects 

 * cd yourRepo
 * git submodule add https://github.com/QuasarApp/Qt-Secret.git # add the repository of Qt-Secret into your repo like submodule
 * git submodule update --init --recursive
 * Add to the list of libraries for the Qt-Secret assembly. For an example you can create Main.Pro in which connect Qt-Secret and your project.pro files as subprojects.
 
 **Main.pro:**
``` qmake
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           Qt-Secret \
           MyProject
```
 * Include in your MyProject.pro file the pri file of Qt-Secret library
  >> include($$PWD/../Qt-Secret/src/Qt-Secret.pri)
 * Rebuild yuor project

## for other build system
 
 * cd yourRepo
 * git submodule add https://github.com/QuasarApp/Qt-Secret.git # add the repository of Qt-Secret into your repo like submodule
 * git submodule update --init --recursive
 * Add the rule for build Qt-Secret
 * Add INCLUDEPATH and LIBS for your build system 
 * Rebuild yuor project


#### Detailed instructions of include in QtCreator see [here](Doc/QtCreator.md).

# Usage

## RSA

### Encryption and decryption of messages.

``` cpp
#include <qrsaencryption.h>
#include <QDebug>

bool testEncryptAndDecryptExample() {

    QByteArray pub, priv;
    QRSAEncryption e(QRSAEncryption::Rsa::RSA_2048);
    e.generatePairKey(pub, priv); // or other rsa size

    QByteArray msg = "test message";

    auto encryptMessage = e.encode(msg, pub);

    if (encryptMessage == msg)
        return false;

    auto decodeMessage = e.decode(encryptMessage, priv);

    return decodeMessage == msg;
}

int main() {
    if (testEncryptAndDecryptExample()) {
        qInfo() << "Success!";
    }
}


```

### Signature and verification of the message signature.

``` cpp
#include <qrsaencryption.h>
#include <QDebug>

bool testExample() {
    QByteArray pub, priv;
    QRSAEncryption e(QRSAEncryption::Rsa::RSA_2048);
    e.generatePairKey(pub, priv); // or other rsa size

    QByteArray msg = "test message";

    auto signedMessage = e.signMessage(msg, priv);

    if (e.checkSignMessage(signedMessage, pub)) {
        qInfo() <<" message signed success";
        return true;
    }

    return false;

}

int main() {
    if (testExample()) {
        qInfo() <<"success!";
    }
}

```

## AES

Sample code using a 128bit key in ECB mode
``` cpp
#include "qaesencryption.h"

QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
QByteArray encodedText = encryption.encode(plainText, key);

QByteArray decodedText = encryption.decode(encodedText, key);
```

Example for 256bit CBC using QString
``` cpp
#include <QCryptographicHash>
#include "qaesencryption.h"

QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
                 "is a specification for the encryption of electronic data established by the U.S. "
                "National Institute of Standards and Technology (NIST) in 2001");
QString key("your-string-key");
QString iv("your-IV-vector");

QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

QString decodedString = QString(encryption.removePadding(decodeText));

//decodedString == inputStr !!! 
```

### Example via static invocation
Static invocation without creating instances, 256 bit key, ECB mode, starting from *QString* text/key
``` cpp
#include <QCryptographicHash>
#include "qaesencryption.h"

QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
                 "is a specification for the encryption of electronic data established by the U.S. "
                "National Institute of Standards and Technology (NIST) in 2001");
QString key("your-string-key");
QString iv("your-IV-vector");

QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

//Static invocation
QByteArray encrypted = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC, 
                        inputStr.toLocal8Bit(), hashKey, hashIV);
//...
// Removal of Padding via Static function
QString decodedString = QString(QAESEncryption::RemovePadding(decodeText));

```

 
