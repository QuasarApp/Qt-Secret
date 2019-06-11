#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += src \
           tests \
           qaesencryption

include($$PWD/test.pri)

src.file = src/Qt-Secret.pro
tests.file = tests/Qt-SecretTest.pro
qaesencryption.file = src/Qt-AES/qaesencryption.pro
