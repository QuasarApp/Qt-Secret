#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

QT -= gui
CONFIG += c++17

TARGET=Qt-SecretTest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

#DEPENDS
CONFIG(release, debug|release): {
    DESTDIR="$$PWD/build/release"
} else {
    DESTDIR="$$PWD/build/debug"
}

include($$PWD/../src/Qt-Secret.pri)

SOURCES += \
    main.cpp
