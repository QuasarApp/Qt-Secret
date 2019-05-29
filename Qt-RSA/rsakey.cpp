#include "rsakey.h"

RsaKey::RsaKey(KeyType type) {
    _type = type;
}

RsaKey::RsaKey(const QString &hex, KeyType type):
    RsaKey(type) {
    fromHex(hex);
}

QString RsaKey::toHex() const {


}

void RsaKey::fromHex(const QString &hex) {
    short sizeExp = static_cast<short>(_type) / 2;

    auto expXex = hex.left(sizeExp);

}

bool RsaKey::isValid() const {

}

void RsaKey::fromByteArray(const QByteArray &array) {

}

QByteArray RsaKey::toByteArray() const {

}
