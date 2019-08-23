#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           minigmp \
           src \
           tests \
           qaesencryption \
           Qt-Secret-GUI


include($$PWD/test.pri)

minigmp.file = src/mini-gmp/GMP.pro
src.file = src/Qt-Secret.pro
tests.file = tests/Qt-SecretTest.pro
qaesencryption.file = src/Qt-AES/qaesencryption.pro
