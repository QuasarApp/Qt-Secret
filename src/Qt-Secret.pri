#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

!isEmpty(Qt_SECRET_LIB):error("Qt-Secret.pri already included")
Qt_SECRET_LIB = 1

#DEPENDS
CONFIG(release, debug|release): {
    Qt_SECRET_LIB_OUTPUT_DIR="$$PWD/build/release"
} else {
    Qt_SECRET_LIB_OUTPUT_DIR="$$PWD/build/debug"
}

lessThan (QT_MINOR_VERSION, 14) {
    unix: LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret
    win32: LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret1
} else {
    unix:android: LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret_$$QT_ARCH
    unix:!android: LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret

    win32: LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret1
}

include($$PWD/mini-gmp/src/GMPIncudePah.pri)

INCLUDEPATH += "$$PWD/Qt-RSA"
INCLUDEPATH += "$$PWD/Qt-AES"
