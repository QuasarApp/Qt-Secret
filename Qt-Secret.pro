#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           minigmp \
           src \
           Qt-Secret-GUI

contains(DEFINES, WITHOUT_GUI): {
    SUBDIRS -= Qt-Secret-GUI
}


lessThan (QT_MINOR_VERSION, 12) {
    message(disable tests!)
} else {
    include($$PWD/test.pri)
    message(enabled tests!)
    SUBDIRS += tests

}

minigmp.file = src/mini-gmp/GMP.pro
src.file = src/Qt-Secret.pro
tests.file = tests/Qt-SecretTest.pro


