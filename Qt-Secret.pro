#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

QT += core
QT -= gui
CONFIG += c++17

TARGET=Qt-Secret
TEMPLATE = lib

DEFINES += Qt-SECRET_LIBRARY

VERSION = 0.0.0.1

HEADERS += \
    Qt-RSA/BigInt.hpp \
    Qt-AES/qaesencryption.h \
    Qt-RSA/qrsaencryption.h

SOURCES += \
    Qt-RSA/qrsaencryption.cpp \
    Qt-AES/qaesencryption.cpp
