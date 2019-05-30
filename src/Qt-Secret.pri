#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

!isEmpty(Qt-SECRET_LIB):error("Qt-Secret.pri already included")
Qt-SECRET_LIB = 1

#DEPENDS
CONFIG(release, debug|release): {
    Qt-SECRET_LIB_OUTPUT_DIR="$$PWD/build/release"
} else {
    Qt-SECRET_LIB_OUTPUT_DIR="$$PWD/build/debug"
}
unix:LIBS += -L$$QUASARAPP_LIB_OUTPUT_DIR -lQt-Secret

win32:LIBS += -L$$QUASARAPP_LIB_OUTPUT_DIR -lQt-Secret0


INCLUDEPATH += "$$PWD/Qt-RSA"
INCLUDEPATH += "$$PWD/Qt-AES"



