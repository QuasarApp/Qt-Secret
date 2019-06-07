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
unix:LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret

win32:LIBS += -L$$Qt_SECRET_LIB_OUTPUT_DIR -lQt-Secret1

#include($$PWD/../uint256_t/uint256.pri)

INCLUDEPATH += "$$PWD/Qt-RSA"
INCLUDEPATH += "$$PWD/Qt-AES"



