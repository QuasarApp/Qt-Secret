# Qt-Secret
Simple encryption library supporting RSA and AES algorithms.

# Futures 
The Qt-Secret library supports the following algorithms:

## RSA
The current implementation of RSA does not provide reliable long-term protection; therefore, to provide consistent protection, use the generated keys as session keys.
#### Supported sizes
 * RSA64 (key size 128bit)
 * RSA128 (key size 256bit)

#### Supported futures 

* Encryption and decryption of messages.
* Signature and verification of the message signature.

## AES
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

### Warning
Current version use __int128 type, and this type not supported in msvc compilers (for windows use mingw64)

 * git clone https://github.com/QuasarApp/Qt-Secret.git
 * cd Qt-Secret
 * git submodule update --init --recursive
 * qmake -r 
 * make -j8
 * make test #(for testing)

# Include

## for qmake projects 

 * cd yourRepo
 * git submodule add https://github.com/QuasarApp/Qt-Secret.git # add the repository of Qt-Secret into your repo like submodule
 * git submodule update --init --update
 * Include in your pro file the pri file of Qt-Secret library
  >> include($$PWD/Qt-Secret/src/Qt-Secret.pri)
 * Rebuild yuor project

## for other build system
 
 * cd yourRepo
 * git submodule add https://github.com/QuasarApp/Qt-Secret.git # add the repository of Qt-Secret into your repo like submodule
 * git submodule update --init --update
 * Add the rule for build Qt-Secret
 * Add INCLUDEPATH and LIBS for your build system 
 * Rebuild yuor project


# Usage

## RSA

### Encryption and decryption of messages.

``` cpp
#include <qrsaencryption.h>

    QByteArray pub, priv;
    QRSAEncryption e;
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_128); // or QRSAEncryption::Rsa::RSA_64
    QByteArray msg = "test message";

    auto encodeData = e.encode(msg, pub);
    auto decodeData = e.decode(encodeData, priv);
    
    

```

### Signature and verification of the message signature.

``` cpp
#include <qrsaencryption.h>

    QByteArray pub, priv;
    QRSAEncryption e;
    e.generatePairKey(pub, priv, QRSAEncryption::Rsa::RSA_128); // or QRSAEncryption::Rsa::RSA_64

    QByteArray msg = "test message";

    auto signedMessage = e.signMessage(msg, priv);

    if (e.checkSignMessage(signedMessage, pub)) {
        // message signed success
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

//decodedString == inputStr !!
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

 
