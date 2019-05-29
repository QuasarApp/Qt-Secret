#ifndef HEXPARSER_H
#define HEXPARSER_H

#include "BigInt.hpp"

#include <QString>

class HexParser
{
public:
    HexParser();
    static BigInt formHex(const QString& hex);
    static QString toHex(const BigInt& hex);

};

#endif // HEXPARSER_H
